#pragma once
#include "Car.h"

/// <summary>
/// Ž©“®‰^“]‚ÌŽÔ
/// </summary>
class CPUCar :
    public Car
{
public:
    CPUCar();
    CPUCar(CarParamater carParam,VECTOR destinaTionPos, int duplicateModelHandle);
    ~CPUCar();
    void Update(const float deltaTime, const bool outsideHitFlag, ItemInfo itemInfo)override;
};

