#include "OriginalMath.h"
#include "Car.h"
#include "Wheels.h"
#include "Utility.h"
#include "ConflictExamineResultInfo.h"
#include "EffekseerForDXLib.h"

Car::Car()
{
	tag = ObjectTag::car;
	radius = radiusValue;
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPos = {};
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
	smokeEffectResource = LoadEffekseerEffect("data/effect/smoke.efkefc", 1.0f);
	conflictEffectResource = LoadEffekseerEffect("data/effect/conflict.efkefc", 1.0f);

}

Car::Car(VECTOR firstPos, VECTOR firstDir, VECTOR firstDestinationPos,SoundPlayer* soundPlayer)
{
	position = firstPos;
	direction = firstDir;
	tag = ObjectTag::car;
	bouncePower = setBouncePower;
	radius = radiusValue;
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPos = firstDestinationPos;
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
	smokeEffectResource = LoadEffekseerEffect("data/effect/smoke.efkefc", 1.0f);
	conflictEffectResource = LoadEffekseerEffect("data/effect/conflict.efkefc", 1.0f);
	accelerationEffectResource = LoadEffekseerEffect("data/effect/accelation.efkefc", 20.0f);

	soundPlayer->Add3DSound(drivingSEAddress);

	soundPlayer->Add3DSound(carClashSEAddress);

	soundPlayer->Add3DSound(carHornSEAddress);
	
	soundPlayer->Add3DSound(drivingSEAddress);
	
}

Car::~Car()
{
	MV1DeleteModel(modelHandle);
	DeleteEffekseerEffect(smokeEffectResource);
	DeleteEffekseerEffect(conflictEffectResource);
	DeleteEffekseerEffect(accelerationEffectResource);
	SAFE_DELETE(wheels);
}
/// <summary>
/// ぶつかった時の処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="conflictInfo"></param>
void Car::ConflictProcess(float deltaTime,const ConflictExamineResultInfo conflictInfo, SoundPlayer* soundPlayer)
{
	switch (conflictInfo.tag)
	{
	case ObjectTag::car:
	case ObjectTag::stage:
	case ObjectTag::obstacle:
		ConflictReaction(deltaTime,conflictInfo,soundPlayer);
		break;
	case ObjectTag::goal:
		destinationPos = conflictInfo.pos;
		break;
	case ObjectTag::acelerationFloor: 

		accelPower += 5.0f;
		break;
	default:
		break;
	}
}

void Car::Draw()
{
	MV1DrawModel(modelHandle);
	wheels->Draw();
}

CarNeighborhoodExamineInfo Car::GetNeighExamineInfo()
{
	CarNeighborhoodExamineInfo examineInfo;
	examineInfo.pos = position;
	examineInfo.range = examineRange;
	return examineInfo;
}

/// <summary>
/// ぶつかった時の処理　減速する
/// </summary>
/// <param name="conflictObjPos"></param>
/// <param name="conflictObjRad"></param>
void Car::ConflictReaction(float deltaTime, const ConflictExamineResultInfo conflictInfo, SoundPlayer* soundPlayer)
{
	soundPlayer->SetSoundVolume(MAX1BYTEVALUE, carClashSEAddress);
	soundPlayer->SetSoundRadius(MAX1BYTEVALUE, carClashSEAddress);
	soundPlayer->SetPosition3DSound(position, carClashSEAddress);
	soundPlayer->Play3DSE(position, carClashSEAddress);

	soundPlayer->SetSoundVolume(MAX1BYTEVALUE, carHornSEAddress);
	soundPlayer->SetSoundRadius(MAX1BYTEVALUE, carHornSEAddress);
	soundPlayer->SetPosition3DSound(position, carHornSEAddress);
	soundPlayer->Play3DSE(position, carHornSEAddress);
	//衝突エフェクト
	int playingEffect = PlayEffekseer3DEffect(conflictEffectResource);
	SetPosPlayingEffekseer3DEffect(playingEffect, position.x, position.y, position.z);
	//衝突処理
	accelPower -= accelPower * colideDecel;
	conflictVec = VSub(position, conflictInfo.pos);
	conflictVec = VNorm(conflictVec);
	conflictVec.y = 0;
	position = VAdd(position, VScale(conflictVec,conflictInfo.radius));
	conflictObjBouncePower = conflictInfo.bouncePower;
}

void Car::DamageReaction(const VECTOR conflictObjPos, const float conflictObjRad)
{
}

/// <summary>
/// 進む方向と速さを更新する
/// </summary>
/// <param name="deltaTime">経過時間</param>
/// <param name="accelVec">次の更新までに進む方向と速さ</param>
void Car::UpdateVelocity(const VECTOR accelVec)
{
	velocity = accelVec;
	//タイヤの向きから進行方向を取る
	float theta = wheels->GetMoveDirTheta(VSize(velocity));
	theta *= gripPower;
	velocity = VTransform(velocity, MGetRotY(theta));
	// ベロシティ加速計算.


	// 上下方向にいかないようにベロシティを整える.
	velocity = VGet(velocity.x, 0, velocity.z);	
}
/// <summary>
/// modelの描画場所を更新
/// </summary>
void Car::UpdateMV1Pos()
{
	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) != 0)
	{
		direction = VNorm(velocity);
	}
	// ポジションを更新.
	position = VAdd(position, velocity);
	if (conflictObjBouncePower > 0.0f)
	{
		conflictObjBouncePower -= conflictObjBouncePower * defaultDecel;
		conflictObjBouncePower = conflictObjBouncePower > 0 ? conflictObjBouncePower : 0;
		position = VAdd(position, VScale(conflictVec,conflictObjBouncePower));
	}
	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, position);
}
/// <summary>
/// 車を回転させる
/// </summary>
void Car::ModelSetMatrix()
{
	// 向きに合わせて回転.
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	// モデルに向いてほしい方向に回転.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * RAGE);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}
/// <summary>
/// 自動操縦。
/// </summary>
/// <param name="deltaTime">フレーム間差分</param>
/// <param name="outsideHitFlag">コース外に出たか</param>
void Car::AutoDrive(const float deltaTime, const bool outsideHitFlag,NeighborhoodInfo neighInfo, SoundPlayer* soundPlayer)
{
	wheelArgumentCarInfo.handleDir = GetHandleDir();
	VECTOR accelVec = GetAccelVec(wheelArgumentCarInfo.handleDir, outsideHitFlag, deltaTime,soundPlayer);
	UpdateVelocity(VScale(accelVec, deltaTime));
	UpdateMV1Pos();
	ModelSetMatrix();
	InitWheelArgumentCarInfo();
	wheels->WheelUpdate(wheelArgumentCarInfo);
}


/// <summary>
/// ハンドルの向きを出す
/// </summary>
/// <returns></returns>
HandleDirection Car::GetHandleDir()
{
	//目的地までの距離
	VECTOR destinationBetween = VSub(destinationPos, position);
	OriginalMath math;
	float angular = math.GetDegreeMisalignment(direction, destinationBetween);
	if (angular > turnProccesLine)
	{
		//車の向いてる方向と目的地までの方向の外積を出して
		//右に曲がるか左に曲がるか調べる
		float crossY = VCross(VNorm(direction), VNorm(destinationBetween)).y;
		if (crossY > 0)
		{
			return HandleDirection::right;
		}
		else
		{
			return HandleDirection::left;
		}
	}
	return HandleDirection::straight;
}

/// <summary>
/// 加速するための処理
/// </summary>
/// <param name="dir">向かってる方向</param>
/// <param name="outsideHitFlag"></param>
/// <returns></returns>
VECTOR Car::GetAccelVec(HandleDirection handleDir, bool outsideHitFlag, float deltaTime, SoundPlayer* soundPlayer)
{
	if (handleDir == HandleDirection::brake)//ブレーキ
	{
		accelPower -= accelPower * breakDecel * deltaTime;

		soundPlayer->StopSound(drivingSEAddress);
		if (!soundPlayer->IsPlaySound(breakeSEAddress))
		{
			soundPlayer->SetSoundRadius(MAX1BYTEVALUE, breakeSEAddress);
			soundPlayer->SetSoundVolume(MAX1BYTEVALUE, breakeSEAddress);
			soundPlayer->SetPosition3DSound(position, breakeSEAddress);
			soundPlayer->Play3DSE(position, breakeSEAddress);
		}
	}
	else if (handleDir != HandleDirection::non)//何も入力していないなら
	{
		// 加速処理.
		accelPower += accelPower > maxSpeed ? 0 : accelSpeed * deltaTime;

		soundPlayer->SetSoundRadius(MAX1BYTEVALUE, drivingSEAddress);
		soundPlayer->SetSoundVolume(MAX1BYTEVALUE, drivingSEAddress);
		soundPlayer->SetPosition3DSound(position, drivingSEAddress);
		if(!soundPlayer->IsPlaySound(drivingSEAddress))
		{

			soundPlayer->Play3DSE(position, drivingSEAddress);
		}
	}

	// 止まっている場合は減速しない.
	if (VSize(velocity) > 0)
	{
		
		//左右に曲がろうとしていたら減速
		if (handleDir != HandleDirection::straight)
		{
			//左右に曲がろうとしたら減速する
			accelPower -= accelPower * gripDecel * deltaTime;
		}
		//コース外に出たら減速
		if (outsideHitFlag)
		{
			accelPower -= accelPower * outsideHitDecel * deltaTime;
		}
	}
	else//止まったら音を止める
	{
		soundPlayer->StopSound(drivingSEAddress);
	}

	return VScale(direction, accelPower);
}

float Car::GetNeighSize(NeighborhoodInfo neighInfo)
{
	float angular = 0;
	float neighSize;
	if (neighInfo.outside.hitFlag)
	{
	}
	return angular;
}

void Car::InitWheelArgumentCarInfo()
{
	wheelArgumentCarInfo.matrix = MV1GetMatrix(modelHandle);
	wheelArgumentCarInfo.direction = direction;
	wheelArgumentCarInfo.velocitySize = VSize(velocity);
}

float Car::GetAccelPower()
{
	return accelPower;
}
