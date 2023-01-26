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

Player::Player(VECTOR firstPos, VECTOR firstDir,VECTOR destinationPos)
	:Car(firstPos,firstDir,destinationPos)
{
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
void Player::Update(const float deltaTime, const bool outsideHitFlag, NeighborhoodInfo neighInfo)
{
	int inputKey = GetJoypadInputState(DX_INPUT_KEY);
	VECTOR accelVec = GetAccelVec(inputKey, outsideHitFlag, deltaTime);
	UpdateVelocity(VScale(accelVec,deltaTime));
	UpdateMV1Pos();
	ModelSetMatrix();
	WheelArgumentCarInfo info = { MV1GetMatrix(modelHandle),direction,VSize(velocity) };
	//右か左か押してたら
	if (inputKey & PAD_INPUT_RIGHT)
	{
		info.handleDir = HandleDirection::right;
	}
	else if (inputKey & PAD_INPUT_LEFT)
	{
		info.handleDir = HandleDirection::left;
	}
	else
	{
		info.handleDir = HandleDirection::straight;
	}
	// タイヤの処理
	wheels->WheelUpdate(info);
#ifdef _DEBUG
	//printfDx("%f,%f\n", accelVec.x,accelVec.z);
	printfDx("%f,%f\n", position.x,position.z);
	printfDx("%f,%f\n", direction.x,direction.z);
#endif
}
/// <summary>
/// 入力情報から進む向きと速さを所得
/// </summary>
/// <param name="inputKey">入力情報</param>
/// <param name="outsideHitFlag">コースの外側にぶつかったかどうか</param>
/// <returns>次の更新までに進む向きと速さ</returns>
VECTOR Player::GetAccelVec(const int inputKey,const bool outsideHitFlag, float deltaTime)
{
	// 上を押していたら加速.
	if (inputKey & PAD_INPUT_UP)
	{
		//速度が最高じゃなかったら加速
		accelPower += accelPower > maxSpeed ? 0 : accelSpeed * deltaTime;

	}
	// 下を押していたら減速.
	else if (inputKey & PAD_INPUT_DOWN)
	{
		accelPower -= accelPower * breakDecel * deltaTime;
	}
	// 止まっている場合は減速しない.
	if (VSize(velocity) > 0)
	{
		// 右か左を押していたらグリップによる減速.
		if (inputKey & PAD_INPUT_RIGHT || inputKey & PAD_INPUT_LEFT)
		{
			accelPower -= accelPower * gripDecel * deltaTime;
		}
		// 何も押さなければ減速.
		else if (inputKey == 0)
		{
			accelPower -= accelPower * defaultDecel * deltaTime;
		}
		//コース外に出たら減速
		if (outsideHitFlag)
		{
			accelPower -= accelPower * outsideHitDecel * deltaTime;
		}
	}
	//printfDx("%f\n", accelPower);
	VECTOR accelVec = VScale(direction, accelPower);
	return accelVec;
}

void Player::Init()
{
	modelHandle = MV1LoadModel("data/model/Player/WhiteCar.mv1");
}
