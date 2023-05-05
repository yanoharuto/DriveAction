#pragma once
#include "Car.h"
class SphereCollider;
class Wheels;
 /// <summary>
 /// プレイヤー(車)
 /// </summary>
 class PlayerCar final: public Car
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <returns></returns>
	PlayerCar(VECTOR firstPos);
	///デストラクタ
    ~PlayerCar();
    /// <summary>
    /// 更新（移動処理）
    /// </summary>
	void Update() override;

private:
	//入力によって走る方向を変える
	void SetInputDir();
	//高さ
	const float setFirstPosY = 6.0f;

	static const CarInfomation setCarParam;
};