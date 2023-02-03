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
	firstPosY = firstPos.y;
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
		checkCount++;
		isGoalConflict = true;
		destinationPos = conflictInfo.pos;
		destinationDir = conflictInfo.dir;
		break;
	case ObjectTag::acelerationFloor: 

		addForcePower = accelPower > maxAddSpeed ? maxAddSpeed : addForcePower + addAccelSpeed;
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
/// <summary>
/// 爆弾で攻撃する
/// </summary>
void Car::BombAttack()
{
}
/// <summary>
/// 空を飛ぶ
/// </summary>
/// <param name="deltaTime"></param>
void Car::Fly(float deltaTime)
{
	//制限時間中か空を飛ぶモードになったら
	if (flyTime > 0 && carMode == CarMode::flying)
	{
		if (position.y < maxHeight)//最高高度より下なら上昇
		{
			flyY += flyPower * deltaTime;
			flyY = flyY < maxHeight ? flyY : maxHeight;
		}
		flyTime -= deltaTime;
	}
	else
	{
		carMode = CarMode::downing;
	}
}
/// <summary>
/// 落下する
/// </summary>
/// <param name="deltaTime"></param>
void Car::Down(float deltaTime)
{
	if (position.y > firstPosY)
	{
		flyY = -downSpeed * deltaTime;
	}
	else
	{
		flyY = 0;
		carMode = CarMode::normal;
	}
}
void Car::FlyUpdate(float deltaTime)
{
	switch (carMode)
	{
	case CarMode::normal:
		flyTime = maxFlyTime;
		break;
	case CarMode::flying:
		Fly(deltaTime);
		break;
	case CarMode::downing:
		Down(deltaTime);
		break;
	default:
		break;
	}
}
/// <summary>
/// 周辺を調べてもらうために必要な情報を渡す
/// </summary>
/// <returns></returns>
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
	//衝突時の衝撃によって移動
	if (conflictObjBouncePower > 0.0f)
	{
		conflictObjBouncePower -= conflictObjBouncePower * defaultDecel;
		conflictObjBouncePower = conflictObjBouncePower > 0 ? conflictObjBouncePower : 0;
		position = VAdd(position, VScale(conflictVec,conflictObjBouncePower));
	}
	if (carMode == CarMode::normal)
	{
		position.y = firstPosY;
	}
	else
	{
		position.y += flyY;
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
void Car::AutoDrive(const float deltaTime, const bool outsideHitFlag,VECTOR pos, SoundPlayer* soundPlayer)
{
	wheelArgumentCarInfo.inputDir = GetAutoDriveDirection();
	VECTOR accelVec = GetAccelVec(wheelArgumentCarInfo.inputDir, outsideHitFlag, deltaTime);
	UpdateVelocity(VScale(accelVec, deltaTime));
	
	UpdateMV1Pos();
	ModelSetMatrix();
	InitWheelArgumentCarInfo();
	wheels->WheelUpdate(wheelArgumentCarInfo);
	PlayDriveSound(wheelArgumentCarInfo.inputDir,soundPlayer);
	bouncePower = setBouncePower + GetAccelPowerPercent() / 100;
}


/// <summary>
/// ハンドルの向きを出す
/// </summary>
/// <returns></returns>
InputInfo Car::GetAutoDriveDirection()
{
	InputInfo inputInfo;
	inputInfo.isBreake = false;
	inputInfo.nonInput = false;
	
	//目的地までの距離
	VECTOR tempVec = isGoalConflict ? destinationDir : VSub(destinationPos, position);
	OriginalMath math;

	float angular = math.GetDegreeMisalignment(direction, tempVec);

	if (angular > turnProccesAngularLine)
	{
		//車の向いてる方向と目的地までの方向の外積を出して
		//右に曲がるか左に曲がるか調べる
		float crossY = VCross(VNorm(direction), VNorm(tempVec)).y;
		if (crossY > 0)
		{

			inputInfo.handleDir = HandleDirection::right;

		}
		else
		{
			inputInfo.handleDir = HandleDirection::left;
		}

	}
	else
	{

		inputInfo.handleDir = HandleDirection::straight;
	}
	
	return inputInfo;
}


VECTOR Car::GetAccelVec(InputInfo inputDir, bool outsideHitFlag, float deltaTime)
{
	
	if (!inputDir.nonInput && !inputDir.isBreake)
	{
		// 加速処理.
		accelPower = accelPower > maxAccelSpeed ? maxAccelSpeed : accelPower + accelAddSpeed * deltaTime;

	}
	// 止まっている場合は減速しない.
	if (VSize(velocity) > 0)
	{
		if (inputDir.isBreake)
		{
			accelPower -= accelPower * breakDecel * deltaTime;
			if (accelPower < stopAccelLine)
			{
				accelPower = 0;
			}
		}
		else if (inputDir.nonInput)
		{
			accelPower -= accelPower * defaultDecel * deltaTime;
			if (accelPower < stopAccelLine)
			{
				accelPower = 0;
			}
		}
		//左右に曲がろうとしていたら減速
		if (inputDir.handleDir!=HandleDirection::straight)
		{
			//左右に曲がろうとしたら減速する
			accelPower -= accelPower * gripDecel * deltaTime;
		}

		//コース外に出たら減速
		if (outsideHitFlag)
		{
			accelPower -= accelPower * outsideHitDecel * deltaTime;
		}
		//外的要因で加速したときに少しずつ元に戻る
		if (addForcePower > 0)
		{
			addForcePower -= addForcePower * defaultDecel * deltaTime;
			addForcePower = addForcePower < 0 ? 0 : addForcePower;
		}
	}

	return VScale(direction, accelPower + addForcePower);
}

void Car::PlayDriveSound(InputInfo inputDir, SoundPlayer* soundPlayer)
{
	if (inputDir.isBreake)
	{
		soundPlayer->StopSound(drivingSEAddress);		
		soundPlayer->SetPosition3DSound(position, breakeSEAddress);
		if (!soundPlayer->IsPlaySound(breakeSEAddress))
		{
			soundPlayer->SetSoundRadius(MAX1BYTEVALUE, breakeSEAddress);
			soundPlayer->SetSoundVolume(MAX1BYTEVALUE, breakeSEAddress);
			soundPlayer->Play3DSE(position, breakeSEAddress);
		}
	}
	else if (!inputDir.nonInput)
	{
		soundPlayer->SetPosition3DSound(position, drivingSEAddress);
		if (!soundPlayer->IsPlaySound(drivingSEAddress))
		{
			soundPlayer->SetSoundRadius(MAX1BYTEVALUE, drivingSEAddress);
			soundPlayer->SetSoundVolume(MAX1BYTEVALUE, drivingSEAddress);
			soundPlayer->Play3DSE(position, drivingSEAddress);
		}
	}
	else
	{
		soundPlayer->StopSound(drivingSEAddress);
	}
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

float Car::GetAccelPowerPercent()
{
	return (accelPower + addForcePower) / (maxAccelSpeed + maxAddSpeed)*100;
}
