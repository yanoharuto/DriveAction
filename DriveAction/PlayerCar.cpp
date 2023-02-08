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
	Init();
}

PlayerCar::PlayerCar(VECTOR firstPos, VECTOR firstDir,VECTOR destinationPos,SoundPlayer* soundPlayer)
	:Car(firstPos,firstDir,destinationPos,soundPlayer)
{
	soundPlayer->SetListener(position,VAdd(position,direction));
	Init();
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
void PlayerCar::Update(const float deltaTime, const bool outsideHitFlag,ItemInfo item,SoundPlayer* soundPlayer)
{

	if (isDamage)
	{
		DamageReaction(deltaTime);
	}
	else
	{
		RecieveItemEffecacy(item, deltaTime);
	}
	SetInputDir();
	Down(deltaTime);
	VECTOR accelVec = GetAccelVec(wheelArgumentCarInfo.inputDir, outsideHitFlag, deltaTime);
	UpdateVelocity(VScale(accelVec, deltaTime));
	UpdateMV1Pos();
	ModelSetMatrix();
	InitWheelArgumentCarInfo();
	PlayDriveSound(wheelArgumentCarInfo.inputDir,soundPlayer);
	// タイヤの処理
	wheels->WheelUpdate(wheelArgumentCarInfo);
	soundPlayer->SetListener(position, VAdd(position, direction));
#ifdef _DEBUG
	//printfDx("%f,%f\n", accelVec.x,accelVec.z);
	//printfDx("position::%f,%f\n", position.x,position.z);
	//printfDx("direction::%f,%f\n", direction.x,direction.z);
#endif
}

void PlayerCar::Init()
{
	modelHandle = MV1LoadModel("data/model/Player/WhiteCar.mv1");
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
