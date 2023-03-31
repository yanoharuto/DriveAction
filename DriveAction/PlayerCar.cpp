#include <math.h>
#include "EffekseerForDXLib.h"
#include "UserInput.h"
#include "PlayerCar.h"
#include "Wheels.h"
#include "Utility.h"	
#include "SoundPlayer.h"
#include "EffectManager.h"
#include "ConflictManager.h"
const CarInfomation PlayerCar::setCarParam =
{
	0.7f,
	4.7f,
	3.0f,
	0.13f,
	1.0f,
	0.34f,
	7.0f,
};
/// <summary>
/// コンストラクタ
/// </summary>
/// <returns></returns>
PlayerCar::PlayerCar()
{
}

PlayerCar::PlayerCar(VECTOR firstPos, HitNumCounter* counter)
	:Car(setCarParam)
{
	damageCoolTimer = new Timer(setDamageCoolTime);
	modelHandle = AssetManager::GetDuplicate3DModelAssetHandle("Player/IceBlades.mv1");
	MV1SetScale(modelHandle, { modelSize,modelSize,modelSize });
	position = firstPos;
	firstPosY = setFirstPosY;
	position.y = firstPosY;
	prevPos = position;
	direction = VGet(0.0f, 0.0f, -1.0f);
	SoundPlayer::SetListener(position,VAdd(position,direction));
	collider = new SphereCollider(this);
	collider->SetCoolTimer(ObjectTag::damageObject, damageCoolTimer);
	counter->SetTimer(ObjectTag::damageObject, damageCoolTimer);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <returns></returns>
PlayerCar::~PlayerCar()
{
	SAFE_DELETE(wheels);

	SoundPlayer::StopSound(drivingSEPass);
	SoundPlayer::StopSound(carClashSEPass);
	SoundPlayer::StopSound(carHornSEPass);
	ConflictManager::EraceConflictObjInfo(collider);
	SAFE_DELETE(collider);
	if (runEffect != -1)
	{
		StopEffekseer3DEffect(runEffect);
		DeleteEffekseerEffect(runEffect);
	}
}

/// <summary>
/// 更新
/// </summary>
void PlayerCar::Update()
{
	VECTOR prevPos = position;
	SetInputDir();
	CommonUpdate();
	PlayDriveSound(wheelArgumentCarInfo.inputDir);
	SoundPlayer::SetListener(position, VAdd(position, direction));
	ArgumentConflictResultInfo resultInfo = GetConflictArgumentInfo();
	resultInfo.pos = position;
	VECTOR damageEffectPos = position;

#ifdef _DEBUG
	printfDx("position::%f,%f,%f\n", position.x,position.y,position.z);
	printfDx("dir::%f,%f,%f\n", direction.x,direction.y,direction.z);
	printfDx("velocity::%f,%f,%f\n", velocity.x,velocity.y,velocity.z);

#endif
}

void PlayerCar::SetInputDir()
{
	wheelArgumentCarInfo.inputDir.isBreake = false;
	//右か左か押してたら
	if (UserInput::GetInputState(Right) == Hold)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::right;
		twistZRota += twistZRotaSpeed;
		
	}
	else if (UserInput::GetInputState(Left) == Hold)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::left;
		twistZRota -= twistZRotaSpeed;
		
	}
	else if (UserInput::GetInputState(Up) == Hold)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::straight;
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
	else//なにも押していない時の処理
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::straight;
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
	if (fabsf(twistZRota) > twistZMaxRota)
	{
		twistZRota = twistZRota > 0 ? twistZMaxRota : -twistZMaxRota;
	}
	if (UserInput::GetInputState(KeyInputKind::Down) == Hold)
	{
		wheelArgumentCarInfo.inputDir.isBreake = true;
		twistZRota -= twistZRota * twistZRotaSpeed;
	}
}
