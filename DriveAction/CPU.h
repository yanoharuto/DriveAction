#pragma once
#include "Racer.h"
#include "CPUCar.h"

class CPU :
    public Racer
{
public:
    CPU();
    CPU(VECTOR firstPos);
    ~CPU();
    void Update(float deltaTime)override;
private:
    CPUCar* cpuCar = nullptr;
    const float setItemCoolTime = 10.0f;
    float itemCoolTime = 0;
};

