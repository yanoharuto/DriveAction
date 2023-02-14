#include "CPU.h"
#include"Utility.h"

CPU::CPU()
{
}

CPU::CPU(CircuitData circuitData, VECTOR firstPos, VECTOR firstDir)
    :Racer(circuitData)
{
    cpuCar = new CPUCar(firstPos, firstDir, checkPoint->GetPos(), soundPlayer);
    SetCarPointer(cpuCar);
}

CPU::~CPU()
{
    SAFE_DELETE(checkPoint);
    SAFE_DELETE(soundPlayer);
    SAFE_DELETE(itemHolder);
    SAFE_DELETE(car);
}
