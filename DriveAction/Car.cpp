#include "Wheels.h"
#include "InputDirection.h"
#include "Car.h"
#include "Utility.h"
#include "ConflictExamineResultInfo.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "SoundPlayer.h"
#include "HitCheckExamineObjectInfo.h"
#include "ObjPosAndDir.h"
#include "Timer.h"

//これ以下の速度になってたらaccelPowerを0にするよ
const float Car:: lowestSpeed = 1.2f;
// なにもしない時の減速.
const float Car::defaultDecel = 0.01f;
// ブレーキ時の減速.
const float Car:: breakDecel = 0.03f;
// グリップの減速.
const float Car:: gripDecel = 0.08f;
// 障害物にぶつかったときの減速率.
const float Car:: colideDecel = 0.98f;
//ダメージを受けた時の操作不可能時間の合計
const float Car:: setDamageReactionTime = 0.5f;
//ダメージを受けた時に回転する速度
const float Car:: damageReactionRotaSpeed = 75.0f;
//ぶつかった時のエフェクト
const EffectKind Car::conflictEffectResource = carConflict;
//走っているときのエフェクト
const EffectKind Car:: windEffectResource = carWind;
//コインを取った時のエフェクトのパス
const EffectKind Car::coinEffectPass = getCoin;
//止まった時の効果音
const std::string Car:: breakeSEPass = "brake.mp3";
//ぶつかった時の効果音
const std::string Car:: carClashSEPass = "carClash.mp3";
//クラクションの効果音
const std::string Car:: carHornSEPass = "carHorn.mp3";
//運転中の効果音
const std::string Car:: drivingSEPass = "driving1.mp3";

Car::Car()
{
	tag = ObjectTag::player;
	UpdateMV1Pos();
	ModelSetMatrix();
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
}
/// <summary>
/// 初期化
/// </summary>
/// <param name="param"></param>
Car::Car(CarInfomation param,Init::InitObjKind kind)
	:Actor(kind)
{
	tag = ObjectTag::player;
	carParam.gripPower = param.gripPower;
	carParam.addSpeed = param.addSpeed;
	carParam.maxSpeed = param.maxSpeed;
	UpdateMV1Pos();
	ModelSetMatrix();
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });

	EffectManager::LoadEffectManager(coinEffectPass);
	EffectManager::LoadEffectManager(conflictEffectResource);
	EffectManager::LoadEffectManager(windEffectResource);
	SoundPlayer::LoadSound(drivingSEPass);
	SoundPlayer::LoadSound(carClashSEPass);
	SoundPlayer::LoadSound(carHornSEPass);
}

Car::~Car()
{
	SoundPlayer::StopSound(drivingSEPass);
	SoundPlayer::StopSound(carClashSEPass);
	SoundPlayer::StopSound(carHornSEPass);
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
	case ObjectTag::player:
	case ObjectTag::stage:
	case ObjectTag::obstacle:
		ConflictReaction(conflictInfo);
		break;
	case ObjectTag::coin:
		coinConflictEffect = EffectManager::GetPlayEffect3D(coinEffectPass);
		SetPosPlayingEffekseer3DEffect(coinConflictEffect, position.x, position.y, position.z);
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
	PlayConflictSound();
	PlayConflictEffect();

	collVec = conflictInfo.bounceVec;
	collVec.y = 0;
	//減速
	accelPower -= accelPower * colideDecel;

	//衝突して移動
	position = conflictInfo.pos;
	position.y = firstPosY;
	MV1SetPosition(modelHandle, position);
}
/// <summary>
/// 車がダメージ判定のある物体にぶつかった時の関数
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="conflictInfo"></param>
void Car::DamageReaction(const ConflictExamineResultInfo conflictInfo)
{
	isDamage = true;
	damageReactionTime = setDamageReactionTime;
	//無敵時間セット
	twistZRota = 0.0f;
	PlayConflictSound();
	PlayConflictEffect();
}
/// <summary>
/// 車がダメージを受けた後に走る処理
/// </summary>
/// <param name="conflictObjPos">ぶつかったオブジェクトの位置</param>
/// <param name="conflictObjRad">ぶつかったオブジェクトの半径</param>
void Car::PostDamageProccess()
{
	//ダメージを受けたならダメージを受けたリアクションをする
	if (isDamage)
	{
		damageReactionTime -= DELTATIME;
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
	//ぶつかった時の衝撃で移動
	if (VSize(collVec) > 0.1f)
	{
		position = VAdd(position, collVec);
		collVec = VScale(collVec, defaultDecel);
	}
	else //衝撃が無くなったら運転できる
	{
		// ポジションを更新.
		position = VAdd(position, velocity);
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
		rota *= damageReactionRotaSpeed;
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
void Car::AutoDrive()
{
	CommonUpdate();
}
/// <summary>
/// 共通処理
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="destinationPos"></param>
/// <param name="itemInfo"></param>
void Car::CommonUpdate()
{
	//落下
	UpDown();
	//ダメージを受けている時は
	PostDamageProccess();
	//速さを所得
	VECTOR accelVec = GetAccelVec(wheelArgumentCarInfo.inputDir);
	//速度を更新
	UpdateVelocity(accelVec);

	//位置の更新
	UpdateMV1Pos();
	//回転とかを制御
	ModelSetMatrix();
	//タイヤに渡したい情報を出す
	InitWheelArgumentCarInfo();
	EffectUpdate();
	//タイヤの更新
	wheels->WheelUpdate(wheelArgumentCarInfo);
}
/// <summary>
/// 移動中のエフェクトとかコインのエフェクトとかを更新
/// /// </summary>
void Car::EffectUpdate()
{
	float degree = OriginalMath::GetDegreeMisalignment(VGet(1, 0, 0), direction);
	//走っている最中に出るエフェクト
	if (VSize(velocity) > 0.5f)
	{
		//走っている最中にもエフェクトが出ているか
		if (runEffect == -1)
		{
			//エフェクトが消えてたら出す
			runEffect = EffectManager::GetPlayEffect3D(windEffectResource);
		}
		//車の場所と回転に合わせる
		SetPosPlayingEffekseer3DEffect(runEffect, position.x, 0, position.z);
		if (VCross(VGet(1, 0, 0), direction).y < 0)
		{
			SetRotationPlayingEffekseer3DEffect(runEffect, 0, -degree * RAGE, 0);
		}
		else
		{
			SetRotationPlayingEffekseer3DEffect(runEffect, 0, degree * RAGE, 0);
		}
	}
	else
	{
		//スピード出ていなかったらエフェクトを消す
		if (runEffect != -1)
		{
			StopEffekseer3DEffect(runEffect);
			runEffect = -1;
		}
	}
	//コインを取った時に出るエフェクトを表示
	if (coinConflictEffect != -1)
	{
		SetPosPlayingEffekseer3DEffect(coinConflictEffect, position.x, position.y, position.z);

	}
}


VECTOR Car::GetAccelVec(InputInfo inputDir )
{
	float decelPower = 0;
	//ブレーキしてなかったら
	if (!inputDir.isBreake)
	{
		// 加速処理.
		accelPower += carParam.addSpeed;

		accelPower += turboPower;
		turboPower = turboPower > 0 ? turboPower - turboPower * defaultDecel : 0;
		if (accelPower > carParam.maxSpeed)
		{
			accelPower = carParam.maxSpeed;
		}
	}
		//左右に曲がろうとしていたら減速
	if (inputDir.handleDir != HandleDirection::straight)
	{
		//左右に曲がろうとしたら減速する
		decelPower = gripDecel;
		if (inputDir.isBreake)
		{
			turboPower = turboPower > 3 ? 3 : turboPower + carParam.addSpeed;

		}
	}

	//ブレーキしていたら減速
	if (inputDir.isBreake)
	{
		decelPower = breakDecel;
	}
	accelPower -= accelPower * decelPower;
	
	//最低速度
	if (accelPower < lowestSpeed)
	{
		accelPower = lowestSpeed;
	}
	printfDx("power::%f\n", accelPower);
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
		if (!SoundPlayer::IsPlaySound(breakeSEPass))
		{
			SoundPlayer::Play2DSE(breakeSEPass);
		}
	}
	else//走行音
	{
		if (!SoundPlayer::IsPlaySound(drivingSEPass))
		{
			SoundPlayer::Play2DSE(drivingSEPass);
		}
	}
}
/// <summary>
/// ぶつかった時の効果音を鳴らす
/// </summary>
void Car::PlayConflictSound()
{
	SoundPlayer::Play3DSE(carClashSEPass);
	SoundPlayer::Play3DSE(carHornSEPass);
}
/// <summary>
/// ぶつかった時のエフェクト
/// </summary>
void Car::PlayConflictEffect()
{
	//衝突エフェクト
	int playingEffect = EffectManager::GetPlayEffect3D(conflictEffectResource);
	SetPosPlayingEffekseer3DEffect(playingEffect, position.x, position.y, position.z);
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
/// 上下に動く
/// </summary>
/// <param name="deltaTime"></param>
void Car::UpDown()
{
	position.y = firstPosY + cos(cosValue) * updownSpeed;
	cosValue += cosAddValue;
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
/// 移動する前のポジションを渡す
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo Car::GetHitCheckExamineInfo()
{
	HitCheckExamineObjectInfo info;
	info.pos = prevPos;
	info.radius = radius;
	info.velocity = velocity;
	return info;
}
