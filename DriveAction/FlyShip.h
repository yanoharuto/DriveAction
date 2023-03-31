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
    virtual ~FlyShip();
    virtual void Update();
    virtual void Init(VECTOR newPosition,VECTOR newDestinationPos);
protected:
};