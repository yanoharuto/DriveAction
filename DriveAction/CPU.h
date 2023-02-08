#pragma once
#include "Racer.h"
#include "CPUCar.h"
class CPU :
    public Racer
{
public:
    CPU();
    CPU(CircuitData circuitData, VECTOR firstPos, VECTOR firstDir);
    ~CPU();
private:
    CPUCar* cpuCar = nullptr;
};

