#pragma once
#include "FlyShip.h"
class LaserFlyShip abstract:
    public FlyShip
{
public:
    LaserFlyShip();
    LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos);
    ~LaserFlyShip();
    virtual void Init(VECTOR playerPos);
    virtual void GenerateLaser() = 0;
private:
    float firstPosY;
    bool isGenerateLaser = false;
    static const float deleteBetween;
};
