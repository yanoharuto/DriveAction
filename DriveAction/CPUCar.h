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
    CPUCar(VECTOR firstPos,VECTOR firstDir ,VECTOR destinationPos,SoundPlayer* soundPlayer);
    ~CPUCar();
    void Update(const float deltaTime, const bool outsideHitFlag, NeighborhoodInfo neighInfo,SoundPlayer* soundPlayer)override;
    
private:
    void Init();
    
};

