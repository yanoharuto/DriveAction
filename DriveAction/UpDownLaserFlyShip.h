#pragma once
#include "LaserFlyShip.h"
class UpDownLaserFlyShip :
    public LaserFlyShip
{
public:
    UpDownLaserFlyShip();
    UpDownLaserFlyShip(VECTOR setPos, VECTOR setDestinationPos);
    ~UpDownLaserFlyShip();
    void Update() override;
    void GenerateLaser()override;
private:
    static const float addMoveValue;
    static const float setFirstPosY;
    static const float updownSpeed;
    float totalMoveValue = 0;
    bool isGenerateLaser = false;
};

