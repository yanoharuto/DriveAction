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
    CPUCar(VECTOR firstPos,VECTOR firstDir);
    ~CPUCar();
    void Update(const float deltaTime, const bool outsideHitFlag, NeighborhoodInfo neighInfo)override;
    
private:
    void Init();
    
};

