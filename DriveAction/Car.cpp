#include "OriginalMath.h"
#include "Car.h"
#include "Wheels.h"
#include "Utility.h"
#include "ConflictExamineResultInfo.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
//車のモデルの大きさ
static const float carModelSize = 0.175f;
//加速量
static const float accelAddSpeed = 38.4f;
// 通常最高速度.
static const float maxAccelSpeed = 230.0f;
//外的要因の速さの最高速度
static const float maxAddForcePower = 100.0f;
//外的要因の速さ
static const float addAccelForce = 8.0f;
//これ以下の速度になってたらaccelPowerを0にするよ
static const float stopAccelLine = 1.0f;
// なにもしない時の減速.
static const float defaultDecel = 0.2f;
// ブレーキ時の減速.
static const float breakDecel = 0.9895f;
// グリップの減速.
static const float gripDecel = 0.205f;
// グリップ力.
static const float gripPower = 0.1f;
// 障害物にぶつかったときの減速率.
static const float colideDecel = 0.2f;
//コースの外側に来た時の減速
static const float outsideHitDecel = 0.28f;
//車の幅
static const float setRadius = 3.8f;
//車の高さ
static const float carHeight = 3.2f;
//目的地に向かうときに曲がるか判断する
static const float turnProccesAngularLine = 5.0f;
//ブレーキをしなければいけないライン
static const float breakeProccesAngularLine = 25.0f;
//跳ね返り力の固定値
static const float setBouncePower = 1.0f;
//降りる速度
static const float downSpeed = 10.8f;
//最初のY座標
static const float firstPosY = -4.0;
//コースアウトから元のコースに戻るまでにかかる時間
static const float setCourceOutProccessTime = 2.5f;
//ダメージを受けた時の操作不可能時間の合計
static const float setDamageReactionTime = 0.8f;
static const float autoDriveValue = 180.0f;
//煙のエフェクト
static const std::string smokeEffectResource = "smoke.efkefc";
//ぶつかった時のエフェクト
static const std::string conflictEffectResource = "conflict.efkefc";
//止まった時の効果音
static const std::string breakeSEAddress = "brake.mp3";
//ぶつかった時の効果音
static const std::string carClashSEAddress = "carClash.mp3";
//クラクションの効果音
static const std::string carHornSEAddress = "carHorn.mp3";
//運転中の効果音
static const std::string drivingSEAddress = "driving1.mp3";
Car::Car()
{
	tag = ObjectTag::car;
	radius = setRadius;
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPos = {};
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });

}

Car::Car(VECTOR firstPos, VECTOR firstDir, VECTOR firstDestinationPos,int duplicateModelHandle)
{
	modelHandle = duplicateModelHandle;
	position = firstPos;
	position.y = firstPosY;
	direction = firstDir;
	tag = ObjectTag::car;
	bouncePower = setBouncePower;
	radius = setRadius;
	MV1SetScale(modelHandle, VGet(carModelSize,carModelSize,carModelSize));
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPos = firstDestinationPos;
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });

	EffectManager::LoadEffectManager(smokeEffectResource,1.0f);
	EffectManager::LoadEffectManager(conflictEffectResource,1.0f);
	
	SoundPlayer::Load3DSound(drivingSEAddress);
	SoundPlayer::Load3DSound(carClashSEAddress);
	SoundPlayer::Load3DSound(carHornSEAddress);
	
	
}

Car::~Car()
{
	MV1DeleteModel(modelHandle);
	SoundPlayer::StopSound(drivingSEAddress);
	SoundPlayer::StopSound(carClashSEAddress);
	SoundPlayer::StopSound(carHornSEAddress);
	SAFE_DELETE(wheels);
}
/// <summary>
/// ぶつかった時の処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="conflictInfo"></param>
void Car::ConflictProccess(float deltaTime,const ConflictExamineResultInfo conflictInfo)
{
	if (!isCourceOutProccessing)
	{
		switch (conflictInfo.tag)
		{
		case ObjectTag::car:
		case ObjectTag::stage:
		case ObjectTag::obstacle:
			ConflictReaction(deltaTime, conflictInfo);
			break;
		case ObjectTag::goal:

			isGoalConflict = true;
			destinationPos = conflictInfo.pos;
			destinationDir = conflictInfo.dir;
			break;
		case ObjectTag::acelerationFloor:
			forcePower += addAccelForce * deltaTime;
			forcePower = forcePower > maxAddForcePower ? maxAddForcePower : forcePower;
			break;
		case ObjectTag::itemBox:

			break;
		case ObjectTag::damageObject:
			isDamage = true;
			damageReactionTime = setDamageReactionTime;
			accelPower = 0;
			forcePower = 0;
			ConflictReaction(deltaTime, conflictInfo);
			break;
		default:
			break;
		}
	}
}

void Car::Draw()
{
	MV1DrawModel(modelHandle);
	wheels->Draw();
}
/// <summary>
/// アイテムに渡したい情報を出す
/// </summary>
/// <returns></returns>
ItemArgumentCarInfo Car::GetItemArgumentInfo()
{
	return { position,direction,velocity,radius };
}

/// <summary>
/// ぶつかった時の処理　減速する
/// </summary>
/// <param name="conflictObjPos"></param>
/// <param name="conflictObjRad"></param>
void Car::ConflictReaction(float deltaTime, const ConflictExamineResultInfo conflictInfo)
{
	SoundPlayer::SetSoundVolume(MAX1BYTEVALUE, carClashSEAddress);
	SoundPlayer::SetSoundRadius(MAX1BYTEVALUE, carClashSEAddress);
	SoundPlayer::SetPosition3DSound(position, carClashSEAddress);
	SoundPlayer::Play3DSE(carClashSEAddress);

	SoundPlayer::SetSoundVolume(MAX1BYTEVALUE, carHornSEAddress);
	SoundPlayer::SetSoundRadius(MAX1BYTEVALUE, carHornSEAddress);
	SoundPlayer::SetPosition3DSound(position, carHornSEAddress);
	SoundPlayer::Play3DSE(carHornSEAddress);
	//衝突エフェクト
	int playingEffect = EffectManager::GetPlayEffect3D(conflictEffectResource);
	SetPosPlayingEffekseer3DEffect(playingEffect, position.x, position.y, position.z);
	//衝突処理
	accelPower -= accelPower * colideDecel;
	conflictVec = VSub(position, conflictInfo.pos);
	conflictVec = VNorm(conflictVec);
	conflictVec.y = 0;
	position = VAdd(position, VScale(conflictVec,conflictInfo.radius));
	conflictObjBouncePower = conflictInfo.bouncePower;
}
/// <summary>
/// 車が攻撃を受けたら関数
/// </summary>
/// <param name="conflictObjPos">ぶつかったオブジェクトの位置</param>
/// <param name="conflictObjRad">ぶつかったオブジェクトの半径</param>
void Car::DamageReaction(float deltaTime)
{
	damageReactionTime -= deltaTime;
	if (damageReactionTime < 0)
	{
		isDamage = false;
	}
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
	theta *= gripPower - (gripPower  * GetTotalAccelPowerPercent()) / 100;
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
	
	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, position);
}
/// <summary>
/// 車を回転させる
/// </summary>
void Car::ModelSetMatrix()
{
	float rota = 0;
	if (isDamage)
	{
		rota = damageReactionTime / setDamageReactionTime * 100;
		rota *= 75.0f;
		
	}
	// 向きに合わせて回転.
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// モデルに向いてほしい方向に回転.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY((180.0f+rota) * RAGE);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}
/// <summary>
/// 自動操縦。
/// </summary>
/// <param name="deltaTime">フレーム間差分</param>
/// <param name="outsideHitFlag">コース外に出たか</param>
void Car::AutoDrive(const float deltaTime, const bool outsideHitFlag, ItemInfo itemInfo)
{
	wheelArgumentCarInfo.inputDir = GetAutoDriveDirection();
	CommonUpdate(deltaTime, outsideHitFlag, itemInfo);
}

void Car::SetCourceOutProccess(VECTOR lastCheckPos, VECTOR lastCheckDir)
{
	if (!isCourceOutProccessing)
	{
		prevDestinationPos = lastCheckPos;
		prevDestinationDir = lastCheckDir;
		isCourceOutProccessing = true;
		courceOutProccessTime = setCourceOutProccessTime;
		velocity = lastCheckDir;
	}
}
void Car::CommonUpdate(const float deltaTime, const bool outsideHitFlag, ItemInfo itemInfo)
{

	if (isCourceOutProccessing)
	{
		CourceOutProccess(deltaTime);
	}
	else
	{
		//落下
		Down(deltaTime);
		if (isDamage)
		{
			DamageReaction(deltaTime);
		}
		else
		{
			RecieveItemEffecacy(itemInfo, deltaTime);
		}
		//速さを所得
		VECTOR accelVec = GetAccelVec(wheelArgumentCarInfo.inputDir, outsideHitFlag, deltaTime);
		//速度を更新
		UpdateVelocity(VScale(accelVec, deltaTime));
		//速さによってはじき返す力を増やす
		bouncePower = setBouncePower + GetTotalAccelPowerPercent() / 100;
	}
	//位置の更新
	UpdateMV1Pos();
	//回転とかを制御
	ModelSetMatrix();
	//タイヤに渡したい情報を出す
	InitWheelArgumentCarInfo();
	//タイヤの更新
	wheels->WheelUpdate(wheelArgumentCarInfo);
}
/// <summary>
/// ハンドルの向きを出す
/// </summary>
/// <returns></returns>
InputInfo Car::GetAutoDriveDirection()
{
	InputInfo inputInfo;
	//ダメージを食らってたら減速
	if (isDamage)
	{
		inputInfo.isBreake = true;
		inputInfo.nonInput = true;
		inputInfo.handleDir = HandleDirection::straight;
		return inputInfo;
	}
	inputInfo.isBreake = false;
	inputInfo.nonInput = false;
	
	//目的地までの距離
	VECTOR tempVec = destinationDir; 
	VECTOR between = VSub(VGet(destinationPos.x, 0, destinationPos.z), VGet(position.x, 0, position.z));
	if (VSize(between) > autoDriveValue)
	{
		tempVec = between;
	}
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
		if (angular > breakeProccesAngularLine && accelPower > maxAccelSpeed / 4)//結構曲がる必要がある場所ならブレーキ
		{
			inputInfo.isBreake = true;
		}
	}
	else
	{
		//曲がらなくていいならまっすぐに
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

		//左右に曲がろうとしていたら減速
		if (inputDir.handleDir != HandleDirection::straight)
		{
			//左右に曲がろうとしたら減速する
			accelPower -= accelPower * gripDecel * deltaTime;
		}

		//コース外に出たら減速
		if (outsideHitFlag && isOnGround)
		{
			accelPower -= accelPower * outsideHitDecel * deltaTime;
		}
		//ブレーキしていたら
		if (inputDir.isBreake)
		{
			accelPower -= accelPower * breakDecel * deltaTime;

			if (accelPower < stopAccelLine)
			{
				accelPower = 0;
			}
		}
		else
		{
			//入力が何もなかったら
			if (inputDir.nonInput)
			{
				accelPower -= accelPower * defaultDecel * deltaTime;
				if (accelPower < stopAccelLine)
				{
					accelPower = 0;
				}
			}
			if (forcePower > 0)
			{
				forcePower -= forcePower * defaultDecel * deltaTime;
				forcePower = forcePower > 0 ? forcePower : 0;
			}
			
		}
	}
	return VScale(direction, accelPower + forcePower);
}
/// <summary>
/// 運転中になる音を再生する
/// </summary>
/// <param name="inputDir"></param>
/// <param name="soundPlayer"></param>
void Car::PlayDriveSound(InputInfo inputDir )
{
	if (inputDir.isBreake)//ブレーキ
	{		
		SoundPlayer::SetPosition3DSound(position, breakeSEAddress);
		if (!SoundPlayer::IsPlaySound(breakeSEAddress))
		{
			SoundPlayer::SetSoundRadius(MAX1BYTEVALUE, breakeSEAddress);
			SoundPlayer::SetSoundVolume(MAX1BYTEVALUE, breakeSEAddress);
			SoundPlayer::Play3DSE(breakeSEAddress);
		}
	}
	else if(inputDir.nonInput)//何も入力してなかったら走行音が無くなる
	{
		SoundPlayer::StopSound(drivingSEAddress);
	}
	else//走行音
	{
		SoundPlayer::SetPosition3DSound(position, drivingSEAddress);
		if (!SoundPlayer::IsPlaySound(drivingSEAddress))
		{
			SoundPlayer::SetSoundRadius(MAX1BYTEVALUE, drivingSEAddress);
			SoundPlayer::SetSoundVolume(MAX1BYTEVALUE, drivingSEAddress);
			SoundPlayer::Play3DSE(drivingSEAddress);
		}
	}
}

/// <summary>
/// タイヤに渡す情報の初期化
/// </summary>
void Car::InitWheelArgumentCarInfo()
{
	wheelArgumentCarInfo.matrix = MV1GetMatrix(modelHandle);
	wheelArgumentCarInfo.direction = direction;
	wheelArgumentCarInfo.velocitySize = VSize(velocity);
}
/// <summary>
/// 落下処理
/// </summary>
/// <param name="deltaTime"></param>
void Car::Down(float deltaTime)
{		//地面に降りれてないなら降りれるようにする
	if (!isOnGround)
	{
		if (position.y > firstPosY)
		{
			position.y = position.y - downSpeed * deltaTime;;
		}
		else
		{
			//地面に降りたらこのまま
			position.y = firstPosY;
			isOnGround = true;
		}
	}
}
void Car::CourceOutProccess(float deltaTime)
{
	if (courceOutProccessTime > 0)
	{
		courceOutProccessTime -= deltaTime;
		float larp = 1.0f - (courceOutProccessTime / setCourceOutProccessTime);
		VECTOR addPos = VScale(VSub(prevDestinationPos, position), larp);
		position = VAdd(addPos, position);		
		position.y = 3.0f;
		isOnGround = false;
	}
	else
	{
		isCourceOutProccessing = false;
	}
}
/// <summary>
/// 今の速度は最大速度の何割なのか所得出来る
/// </summary>
/// <returns></returns>
float Car::GetTotalAccelPowerPercent()
{
	return (accelPower + forcePower) / (maxAccelSpeed + maxAddForcePower) * 100;
}

float Car::GetTotalAccelPower()
{
	return accelPower+forcePower;
}

/// <summary>
/// アイテムの効果を受け取る
/// </summary>
/// <param name="item"></param>
/// <param name="deltaTime"></param>
void Car::RecieveItemEffecacy(ItemInfo itemInfo,float deltaTime)
{
	if (itemInfo.itemTag != non && !isDamage)
	{
		//アイテム使用中ならその効果を受ける
		if (itemInfo.itemSituation == ItemUseSituation::Useing)
		{
			switch (itemInfo.itemTag)
			{
			case kite:
				position.y = itemInfo.effecacyValue;
				forcePower += itemInfo.effecacyValue * deltaTime;

				isOnGround = false;
				break;
			case accelerator:
				forcePower += itemInfo.effecacyValue * deltaTime;
				break;
			}
		}
	}
}
