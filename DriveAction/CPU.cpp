#include "CPU.h"
#include"Utility.h"

CPU::CPU()
{
}

CPU::CPU(CircuitData circuitData, VECTOR firstPos, VECTOR firstDir)
    :Racer(circuitData)
{
    cpuCar = new CPUCar(firstPos, firstDir, checkPoint->GetPos());
    SetCarPointer(cpuCar);
}

CPU::~CPU()
{
}
