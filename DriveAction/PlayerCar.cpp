#include "PlayerCar.h"
#include "Wheels.h"
#include "Utility.h"	
#include <math.h>
#include "EffekseerForDXLib.h"
/// <summary>
/// コンストラクタ
/// </summary>
/// <returns></returns>
PlayerCar::PlayerCar()
{
}

PlayerCar::PlayerCar(VECTOR firstPos, VECTOR firstDir, VECTOR destinationPos, int duplicateModelHandle)
	:Car(firstPos,firstDir,destinationPos,duplicateModelHandle)
{
	SoundPlayer::SetListener(position,VAdd(position,direction));
}

/// <summary>
/// デストラクタ
/// </summary>
/// <returns></returns>
PlayerCar::~PlayerCar()
{
	MV1DeleteModel(modelHandle);
	SAFE_DELETE(wheels);
}

/// <summary>
/// 更新
/// </summary>
void PlayerCar::Update(const float deltaTime, const bool outsideHitFlag,ItemInfo item)
{
	SetInputDir();
	CommonUpdate(deltaTime, outsideHitFlag, item);
	PlayDriveSound(wheelArgumentCarInfo.inputDir);
	SoundPlayer::SetListener(position, VAdd(position, direction));
#ifdef _DEBUG
	//printfDx("%f,%f\n", accelVec.x,accelVec.z);
	//printfDx("position::%f,%f\n", position.x,position.z);
	//printfDx("direction::%f,%f\n", direction.x,direction.z);
#endif
}

void PlayerCar::SetInputDir()
{
	int inputKey = GetJoypadInputState(DX_INPUT_KEY);

	wheelArgumentCarInfo.inputDir.isBreake = false;
	wheelArgumentCarInfo.inputDir.nonInput = false;
	//右か左か押してたら
	if (inputKey & PAD_INPUT_RIGHT)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::right;

	}
	else if (inputKey & PAD_INPUT_LEFT)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::left;
	}
	else if (inputKey & PAD_INPUT_UP)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::straight;
	}
	else//なにも押していない時の処理
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::straight;
		wheelArgumentCarInfo.inputDir.isBreake = false;
		wheelArgumentCarInfo.inputDir.nonInput = true;
	}
	if (inputKey & PAD_INPUT_DOWN)
	{
		wheelArgumentCarInfo.inputDir.isBreake = true;
		wheelArgumentCarInfo.inputDir.nonInput = false;
	}
}
