#pragma once
#include "Car.h"

/// <summary>
/// �����^�]�̎�
/// </summary>
class CPUCar :
    public Car
{
public:
    CPUCar();
    CPUCar(VECTOR firstPos,VECTOR firstDir ,VECTOR destinationPos);
    ~CPUCar();
    void Update(const float deltaTime, const bool outsideHitFlag, ItemInfo itemInfo)override;
private:
    void Init();

};

