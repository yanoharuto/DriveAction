#pragma once
#include "Car.h"
#include "AssetManager.h"
/// <summary>
/// Ž©“®‰^“]‚ÌŽÔ
/// </summary>
class CPUCar :
    public Car
{
public:
    CPUCar();
    CPUCar(VECTOR firstPos,VECTOR destinaTionPos);
    ~CPUCar();
    void Update(const float deltaTime, VECTOR destinationPos, ItemInfo itemInfo)override;
private:
    const float firstPosY = 60.0f;
};

