#pragma once
#include "Car.h"
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
	PlayerCar(VECTOR firstPos,VECTOR firstDir,VECTOR destinationPos, int duplicateModelHandle);
	///デストラクタ
    ~PlayerCar();
    /// <summary>
    /// 更新（移動処理）
    /// </summary>
	void Update(const float deltaTime, const bool outsideHitFlag,ItemInfo itemInfo) override;
	HandleDirection GetHandleDirection();
private:
	void SetInputDir();
};