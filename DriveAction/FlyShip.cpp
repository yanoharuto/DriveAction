#include "FlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
FlyShip::FlyShip()
{
}

FlyShip::FlyShip(FlyShipArgumentInfo flyShipInitInfo)
{
    maxHeight = flyShipInitInfo.maxHeight;
    upSpeed = flyShipInitInfo.addUpSpeed;
    setCoolTime = flyShipInitInfo.setCoolTime;
    aliveTimer = new Timer(flyShipInitInfo.setAliveTime);
}

FlyShip::~FlyShip()
{
    SAFE_DELETE(aliveTimer);
}

void FlyShip::Update(const float deltaTime)
{
   
}

void FlyShip::Init(VECTOR newPosition, VECTOR newDestinationPos)
{
    position = newPosition;
    position.y = firstPosY;
    destinationPosition = newDestinationPos;
    destinationPosition.y = firstPosY;
    direction = VNorm(VSub(destinationPosition, position));
    aliveTimer->Init();
    aliveFlag = true;
}

FlyShipKind FlyShip::GetFlyShipKind()
{
    return shipKInd;
}

void FlyShip::Up(float deltaTime)
{
    position.y += upSpeed * deltaTime;
    if (position.y > maxHeight)
    {
        position.y = maxHeight;
        isMaxHeihgt = true;
    }
}

void FlyShip::Down(float deltaTime)
{
    position.y -= upSpeed * deltaTime;
    if (position.y < minHeight)
    {
        position.y = minHeight;
        isMinHeihgt = true;;
    }
}
