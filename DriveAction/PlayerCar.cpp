#include <math.h>
#include "EffekseerForDXLib.h"
#include "UserInput.h"
#include "PlayerCar.h"
#include "Wheels.h"
#include "Utility.h"	
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <returns></returns>
PlayerCar::PlayerCar()
{
}

PlayerCar::PlayerCar(CarParamater carParam, int duplicateModelHandle)
	:Car(carParam,duplicateModelHandle)
{
	SoundPlayer::SetListener(position,VAdd(position,direction));
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <returns></returns>
PlayerCar::~PlayerCar()
{
	MV1DeleteModel(modelHandle);
	SAFE_DELETE(wheels);
}

/// <summary>
/// �X�V
/// </summary>
void PlayerCar::Update(const float deltaTime, const bool outsideHitFlag,ItemInfo item)
{
	SetInputDir();
	CommonUpdate(deltaTime, outsideHitFlag, item);
	PlayDriveSound(wheelArgumentCarInfo.inputDir);
	SoundPlayer::SetListener(position, VAdd(position, direction));
#ifdef _DEBUG
	//printfDx("%f,%f\n", accelVec.x,accelVec.z);
	printfDx("position::%f,%f\n", position.x,position.z);
	//printfDx("direction::%f,%f\n", direction.x,direction.z);
#endif
}

void PlayerCar::SetInputDir()
{

	wheelArgumentCarInfo.inputDir.isBreake = false;
	wheelArgumentCarInfo.inputDir.nonInput = false;
	//�E�����������Ă���
	if (UserInput::GetInputState(Right)==Hold)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::right;

	}
	else if (UserInput::GetInputState(Left) == Hold)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::left;
	}
	else if (UserInput::GetInputState(Up) == Hold)
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::straight;
	}
	else//�Ȃɂ������Ă��Ȃ����̏���
	{
		wheelArgumentCarInfo.inputDir.handleDir = HandleDirection::straight;
		wheelArgumentCarInfo.inputDir.isBreake = false;
		wheelArgumentCarInfo.inputDir.nonInput = true;
	}
	if (UserInput::GetInputState(KeyInputKind::Down) == Hold)
	{
		wheelArgumentCarInfo.inputDir.isBreake = true;
		wheelArgumentCarInfo.inputDir.nonInput = false;
	}
}
