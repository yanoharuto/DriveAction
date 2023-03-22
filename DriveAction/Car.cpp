#include "OriginalMath.h"
#include "Car.h"
#include "Wheels.h"
#include "Utility.h"
#include "ConflictExamineResultInfo.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "DirectionOfTravelGenerator.h"
#include "SoundPlayer.h"
//これ以下の速度になってたらaccelPowerを0にするよ
const float Car:: stopAccelLine = 40.0f;
// なにもしない時の減速.
const float Car::defaultDecel = 0.78f;
// ブレーキ時の減速.
const float Car:: breakDecel = 0.3895f;
// グリップの減速.
const float Car:: gripDecel = 0.205f;
// 障害物にぶつかったときの減速率.
const float Car:: colideDecel = 0.68f;
//降りる速度
const float Car:: fallSpeed = 10.8f;
//ダメージを受けた時の操作不可能時間の合計
const float Car:: setDamageReactionTime = 0.5f;
//煙のエフェクト
const std::string Car:: smokeEffectResource = "smoke.efkefc";
//ぶつかった時のエフェクト
const std::string Car:: conflictEffectResource = "conflict.efkefc";
const std::string Car:: windEffectResource = "sandWind.efkefc";
//止まった時の効果音
const std::string Car:: breakeSEAddress = "brake.mp3";
//ぶつかった時の効果音
const std::string Car:: carClashSEAddress = "carClash.mp3";
//クラクションの効果音
const std::string Car:: carHornSEAddress = "carHorn.mp3";
//運転中の効果音
const std::string Car:: drivingSEAddress = "driving1.mp3";
Car::Car()
{
	tag = ObjectTag::car;
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPosition = {};
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });

}

Car::Car(CarInfomation param)
{
	turnProccesAngularLine = param.turnAngularLine;
	modelSize = param.modelSize;
	tag = ObjectTag::car;
	setBouncePower = param.bouncePower;
	bouncePower = setBouncePower;
	carParam.gripPower = param.gripPower;
	radius = param.setRadius;
	carParam.addSpeed = param.addSpeed;
	carParam.maxSpeed = param.maxSpeed;
	UpdateMV1Pos();
	ModelSetMatrix();
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });

	EffectManager::LoadEffectManager(smokeEffectResource, 1.0f);
	EffectManager::LoadEffectManager(conflictEffectResource, 1.0f);
	EffectManager::LoadEffectManager(windEffectResource, 10.0f);
	SoundPlayer::Load3DSound(drivingSEAddress);
	SoundPlayer::Load3DSound(carClashSEAddress);
	SoundPlayer::Load3DSound(carHornSEAddress);
}

Car::~Car()
{
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
void Car::ConflictProccess(const ConflictExamineResultInfo conflictInfo)
{
	switch (conflictInfo.tag)
	{
	case ObjectTag::car:
	case ObjectTag::stage:
	case ObjectTag::obstacle:
		ConflictReaction(conflictInfo);
		break;
	case ObjectTag::acelerationFloor:
		
		break;
	case ObjectTag::itemBox:

		break;
	case ObjectTag::damageObject:
		DamageReaction(conflictInfo);
		break;
	default:
		break;
	}

}

/// <summary>
/// ぶつかった時の処理　減速する
/// </summary>
/// <param name="conflictObjPos"></param>
/// <param name="conflictObjRad"></param>
void Car::ConflictReaction(const ConflictExamineResultInfo conflictInfo)
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

	collVec = conflictInfo.bounceVec;
	collVec.y = 0;
	//減速
	accelPower -= accelPower * colideDecel;

	//衝突して移動
	position = conflictInfo.pos;
	position.y = firstPosY;
	MV1SetPosition(modelHandle, position);
}
void Car::DamageReaction(const ConflictExamineResultInfo conflictInfo)
{
	isDamage = true;
	damageReactionTime = setDamageReactionTime;
	accelPower = 0;
	ConflictReaction(conflictInfo);
}
/// <summary>
/// 車がダメージを受けてたら
/// </summary>
/// <param name="conflictObjPos">ぶつかったオブジェクトの位置</param>
/// <param name="conflictObjRad">ぶつかったオブジェクトの半径</param>
void Car::PostDamageProccess(float deltaTime)
{
	if (isDamage)
	{
		damageReactionTime -= deltaTime;
		if (damageReactionTime < 0)
		{
			isDamage = false;
		}
	}
}

/// <summary>
/// 進む方向と速さを更新する
/// </summary>
/// <param name="deltaTime">経過時間</param>
/// <param name="accelVec">次の更新までに進む方向と速さ</param>
void Car::UpdateVelocity(const VECTOR accelVec)
{
	//タイヤの向きから進行方向を取る
	float theta = wheels->GetMoveDirTheta(VSize(accelVec));
	theta *= carParam.gripPower - (carParam.gripPower  * GetTotalAccelPowerPercent()) / 100;
	velocity = VTransform(accelVec, MGetRotY(theta));
	// 上下方向にいかないようにベロシティを整える.
	velocity = VGet(velocity.x, 0, velocity.z);	
}
/// <summary>
/// modelの描画場所を更新
/// </summary>
void Car::UpdateMV1Pos()
{
	//更新する前のポジションを保存
	prevPos = position;
	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(velocity) != 0)
	{
		direction = VNorm(velocity);
	}
	// ポジションを更新.
	position = VAdd(position, velocity);
	if (VSize(collVec) != 0)
	{
		position = VAdd(position, collVec);
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
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), twistZRota);
	// モデルに向いてほしい方向に回転.
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY((180.0f + rota) * RAGE);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}
/// <summary>
/// 自動操縦。
/// </summary>
/// <param name="deltaTime">フレーム間差分</param>
/// <param name="outsideHitFlag">コース外に出たか</param>
void Car::AutoDrive(const float deltaTime, VECTOR destinationPos, ItemInfo itemInfo)
{
	wheelArgumentCarInfo.inputDir = GetAutoDriveDirection();
	CommonUpdate(deltaTime, destinationPos,itemInfo);
}
/// <summary>
/// 共通処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="destinationPos"></param>
/// <param name="itemInfo"></param>
void Car::CommonUpdate(const float deltaTime, VECTOR destinationPos, ItemInfo itemInfo)
{
	destinationPosition = destinationPos;
	//落下
	Down(deltaTime);
	//ダメージを受けている時は
	PostDamageProccess(deltaTime);
	//ダメージを受けていないならアイテムの効果を得る
	if (!isDamage)
	{
		RecieveItemEffecacy(itemInfo, deltaTime);
	}
	//速さを所得
	VECTOR accelVec = GetAccelVec(wheelArgumentCarInfo.inputDir, deltaTime);
	//速度を更新
	UpdateVelocity(VScale(accelVec, deltaTime));
	//速さによってはじき返す力を増やす
	bouncePower = setBouncePower + GetTotalAccelPowerPercent();

	//位置の更新
	UpdateMV1Pos();
	//回転とかを制御
	ModelSetMatrix();
	//タイヤに渡したい情報を出す
	InitWheelArgumentCarInfo();
	printfDx("effect%d\n", playEffect);
	printfDx("velocity%f\n", VSize(velocity));
	if (VSize(velocity) > 0.5f)
	{
		if (playEffect != -1)
		{
			SetPosPlayingEffekseer3DEffect(playEffect, prevPos.x, 0, prevPos.z);
			float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
			SetRotationPlayingEffekseer3DEffect(playEffect, 0, degree * RAGE, 0);
		}
		else
		{
			playEffect = EffectManager::GetPlayEffect3D(windEffectResource);
			SetPosPlayingEffekseer3DEffect(playEffect, prevPos.x, 0, prevPos.z);
			float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
			SetRotationPlayingEffekseer3DEffect(playEffect, 0, degree * RAGE, 0);
		}
	}
	else
	{
		if (playEffect != -1)
		{
			StopEffekseer3DEffect(playEffect);
			DeleteEffekseerEffect(playEffect);
			playEffect = -1;
		}
	}
	//タイヤの更新
	wheels->WheelUpdate(wheelArgumentCarInfo);
}
/// <summary>
/// ハンドルの向きを出す
/// </summary>
/// <returns></returns>
InputInfo Car::GetAutoDriveDirection()
{
	autoDriveP.direction = direction;
	autoDriveP.position = position;
	autoDriveP.turnProccessLine = turnProccesAngularLine;
	return DirectionOfTravelGenerator::GetNextPointDirection(autoDriveP,destinationPosition);
}


VECTOR Car::GetAccelVec(InputInfo inputDir, float deltaTime)
{
	if (fabsf(VSize(collVec)) > 0.1f)
	{
		collVec = VScale(collVec, defaultDecel);
	}
	//ブレーキしてなかったら
	if (!inputDir.isBreake)
	{
		// 加速処理.
		accelPower =  accelPower + carParam.addSpeed * deltaTime;
		if (accelPower > carParam.maxSpeed)
		{
			accelPower = carParam.maxSpeed ;
		}
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

		//ブレーキしていたら減速
		if (inputDir.isBreake)
		{
			accelPower -= accelPower * breakDecel * deltaTime;
		}
		if (accelPower < 0)
		{
			accelPower = 0;
		}

	}
	return VScale(direction, accelPower);
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
{
	position.y += (firstPosY - fabsf(position.y)) * fallSpeed * deltaTime;
}

/// <summary>
/// 今の速度は最大速度の何割なのか所得出来る
/// </summary>
/// <returns></returns>
float Car::GetTotalAccelPowerPercent()
{
	return (accelPower) / (carParam.maxSpeed ) * 100;
}

float Car::GetTotalAccelPower()
{
	return accelPower ;
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
				
				isOnGround = false;
				break;
			case bomber:
				
				break;
			}
		}
	}
}

ObjInfo Car::GetCarPosAndDir()
{
	ObjInfo argumentInfo = {};
	argumentInfo.dir = direction;
	argumentInfo.pos = position;
	argumentInfo.modelSize = modelSize;
	return argumentInfo;
}

HitCheckExamineObjectInfo Car::GetHitCheckExamineInfo()
{
	HitCheckExamineObjectInfo info;
	info.pos = prevPos;
	info.radius = radius;
	info.velocity = VAdd(velocity,collVec);
	return info;
}
