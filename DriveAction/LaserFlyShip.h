#pragma once
#include "FlyShip.h"
class LaserFlyShip :
    public FlyShip
{
public:
    LaserFlyShip();
    LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos);
    ~LaserFlyShip();
    void Init(VECTOR newPosition, VECTOR newDestinationPos) override;
    void Update(const float deltaTime) override;
private:
    bool isGenerateLaser = false;
    static const float setFirstPosY;
    static const float setModelSize;
    static const FlyShipArgumentInfo setFlyShipParam;
};
