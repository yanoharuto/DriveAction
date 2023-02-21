#pragma once
#include "Racer.h"
#include "CPUCar.h"
class CPU :
    public Racer
{
public:
    CPU();
    CPU(VECTOR firstPos, int duplicateModel);
    ~CPU();
    void Update(float deltaTime, bool outsideHitFlag, DamageObjectGenerator* damageObj)override;
    
private:
    CPUCar* cpuCar = nullptr;
};

