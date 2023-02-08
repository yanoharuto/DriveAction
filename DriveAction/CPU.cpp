#include "CPU.h"

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

}
