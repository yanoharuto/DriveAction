#include <math.h>
#include "EffekseerForDXLib.h"
#include "UserInput.h"
#include "PlayerCar.h"
#include "Wheels.h"
#include "Utility.h"	
#include "SoundPlayer.h"
#include "EffectManager.h"
#include "ConflictManager.h"
#include "AssetManager.h"
#include "SphereCollider.h"
const CarInfomation PlayerCar::setCarParam =
{
	1.0f,
	10.0f,
	3.0f,
	0.13f,
	1.0f,
	0.34f,
	7.0f,
};

PlayerCar::PlayerCar(VECTOR firstPos)
	:Car(setCarParam,Init::player)
{
	
	firstPosY = position.y;
	position = firstPos;
	position.y = firstPosY;

	prevPos = position;
	direction = VGet(0.0f, 0.0f, -1.0f);
	SoundPlayer::SetListener(position,VAdd(position,direction));
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
