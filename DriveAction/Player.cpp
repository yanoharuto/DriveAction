#include "Player.h"
#include "Wheels.h"
#include "Utility.h"	
#include <math.h>
#include "EffekseerForDXLib.h"
/// <summary>
/// コンストラクタ
/// </summary>
/// <returns></returns>
Player::Player()
{
	Init();
}

Player::Player(VECTOR firstPos, VECTOR firstDir,VECTOR destinationPos,SoundPlayer* soundPlayer)
	:Car(firstPos,firstDir,destinationPos,soundPlayer)
{
	soundPlayer->SetListener(position,VAdd(position,direction));
	Init();
}

/// <summary>
/// デストラクタ
/// </summary>
/// <returns></returns>
Player::~Player()
{
	MV1DeleteModel(modelHandle);
	SAFE_DELETE(wheels);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update(const float deltaTime, const bool outsideHitFlag, NeighborhoodInfo neighInfo,SoundPlayer* soundPlayer)
{
	VECTOR accelVec = GetAccelVec(GetHandleDir(), outsideHitFlag, deltaTime, soundPlayer);
	UpdateVelocity(VScale(accelVec, deltaTime));
	UpdateMV1Pos();
	ModelSetMatrix();
	InitWheelArgumentCarInfo();
	int inputKey = GetJoypadInputState(DX_INPUT_KEY);

	//右か左か押してたら
	if (inputKey & PAD_INPUT_RIGHT)
	{
		wheelArgumentCarInfo.handleDir = HandleDirection::right;


	}
	else if (inputKey & PAD_INPUT_LEFT)
	{
		wheelArgumentCarInfo.handleDir = HandleDirection::left;

	}
	else if (inputKey & PAD_INPUT_UP)
	{
		wheelArgumentCarInfo.handleDir = HandleDirection::straight;
	}
	else
	{
		wheelArgumentCarInfo.handleDir = HandleDirection::non;
	}
	if (inputKey & PAD_INPUT_DOWN)
	{
		if (wheelArgumentCarInfo.handleDir != HandleDirection::brake)
		{
			wheelArgumentCarInfo.handleDir = HandleDirection::brake;
		}
	}
	// タイヤの処理
	wheels->WheelUpdate(wheelArgumentCarInfo);
	soundPlayer->SetListener(position, VAdd(position, direction));
#ifdef _DEBUG
	//printfDx("%f,%f\n", accelVec.x,accelVec.z);
	//printfDx("%f,%f\n", position.x,position.z);
	//printfDx("%f,%f\n", direction.x,direction.z);
#endif
}

void Player::Init()
{
	modelHandle = MV1LoadModel("data/model/Player/WhiteCar.mv1");
}
