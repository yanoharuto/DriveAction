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
    void Update(float deltaTime,bool outsideHitFlag)override;
    
private:
    void Init();
    
};

