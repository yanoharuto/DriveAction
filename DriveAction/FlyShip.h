#pragma once
#include "Actor.h"
#include "FlyShipArgumentInfo.h"
#include "Timer.h"
#include "FlyShipKind.h"
#include "FiringObjOwner.h"
/// <summary>
/// îÚçsëD
/// </summary>
class FlyShip abstract:
    public Actor,public FiringObjOwner
{
public:
    FlyShip();
    FlyShip(FlyShipArgumentInfo flyShipInitInfo);
    virtual ~FlyShip();
    virtual void Update(const float deltaTime);
    virtual void Init(VECTOR newPosition,VECTOR newDestinationPos);
    FlyShipKind GetFlyShipKind();
protected:
    void Up(float deltaTime);
    void Down(float deltaTime);
    Timer* aliveTimer;
    bool isMaxHeihgt = false;
    bool isMinHeihgt = false;
    float setCoolTime = 0.0f;
    float coolTime = -1;
    float upSpeed = 0;
    float maxHeight = 0;
    float minHeight = 0;
    float firstPosY = 0;
    VECTOR destinationPosition;
    FlyShipKind shipKInd;
};