#pragma once
#include "Car.h"
#include "AssetManager.h"
#include "SphereCollider.h"
#include "HitNumCounter.h"
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
	PlayerCar();
	PlayerCar(VECTOR firstPos,HitNumCounter* counter);
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
	const float setDamageCoolTime = 1.5f;
	//球当たり判定
	SphereCollider* collider;
	static const CarInfomation setCarParam;
};