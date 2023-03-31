#pragma once
#include "LaserFlyShip.h"

class CircleLaserFlyShip :
    public LaserFlyShip
{
public:
    CircleLaserFlyShip();
    CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos);
    void GenerateLaser() override;
private:
    float firstPosY;
    bool isGenerateLaser = false;
    static const float setFirstPosY;
    static const float setModelSize;

};

