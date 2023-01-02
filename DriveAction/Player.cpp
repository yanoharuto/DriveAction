#include "Player.h"
#include "Wheels.h"
#include "Utility.h"	
#include <math.h>

/// <summary>
/// コンストラクタ
/// </summary>
/// <returns></returns>
Player::Player()
{
	modelHandle = MV1LoadModel("data/model/Player/WhiteCar.mv1");
	position = firstPos;
	direction = firstDir;
	tag = ObjectTag::car;
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
void Player::Update(const float deltaTime, const bool outsideHitFlag)
{
	int inputKey = GetJoypadInputState(DX_INPUT_KEY);

	UpdateVelocity(deltaTime, GetAccelVec(inputKey, outsideHitFlag));
	UpdateMV1Pos();
	ModelSetMatrix();
	ArgumentCarInfo info = { MV1GetMatrix(modelHandle),direction,VSize(velocity) };
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
}
/// <summary>
/// 入力情報から進む向きと速さを所得
/// </summary>
/// <param name="inputKey">入力情報</param>
/// <param name="outsideHitFlag">コースの外側にぶつかったかどうか</param>
/// <returns>次の更新までに進む向きと速さ</returns>
VECTOR Player::GetAccelVec(const int inputKey,const bool outsideHitFlag)
{
	// 加速処理.
	VECTOR accelVec = VGet(0, 0, 0);
	// 上を押していたら加速.
	if (inputKey & PAD_INPUT_UP)
	{
		accelPower += accelPower > maxSpeed ? 0 : accelSpeed;
	}
	// 下を押していたら減速.
	else if (inputKey & PAD_INPUT_DOWN)
	{
		accelPower -= accelPower * breakDecel;
	}
	// 止まっている場合は減速しない.
	if (VSize(velocity) > 0)
	{
		// 右か左を押していたらグリップによる減速.
		if (inputKey & PAD_INPUT_RIGHT || inputKey & PAD_INPUT_LEFT)
		{
			accelPower -= accelPower * gripDecel;
		}
		// 何も押さなければ減速.
		if (inputKey == 0)
		{
			accelPower -= accelPower * defaultDecel;
		}
		//コース外に出たら減速
		if (outsideHitFlag)
		{
			accelPower -= accelPower * outsideHitDecel;
		}
	}
	accelVec = VScale(direction, accelPower);
	return accelVec;
}
