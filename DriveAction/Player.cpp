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
	wheels->WheelUpdate(info);
#ifdef _DEBUG
	printfDx("%f,%f\n", position.x, position.z);
	printfDx("%f,%f\n", direction.x, direction.z);
#endif
}
/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	MV1DrawModel(modelHandle);
	wheels->Draw();
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
		accel += accel > maxSpeed ? 0 : accelSpeed;

		accelVec = VScale(direction, accel);
	}
	// 下を押していたら減速.
	else if (inputKey & PAD_INPUT_DOWN)
	{
		accel += accel * breakDecel;
		accelVec = VScale(direction, accel);
	}
	// 止まっている場合は減速しない.
	if (VSize(velocity) > 0)
	{
		// 右か左を押していたらグリップによる減速.
		if (inputKey & PAD_INPUT_RIGHT || inputKey & PAD_INPUT_LEFT)
		{
			accel += accel * gripDecel;
			accelVec = VScale(direction, accel);
		}
		// 何も押さなければ減速.
		if (inputKey == 0)
		{
			accel += accel * defaultDecel;
			accelVec = VScale(direction, accel);
		}
		//コース外に出たら減速
		if (outsideHitFlag)
		{
			accel += accel * outsideHitDecel;
			accelVec = VScale(direction, accel);
		}
	}
	return accelVec;
}
