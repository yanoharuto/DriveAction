#include "UpDownLaserFlyShip.h"
#include "ItemArgumentCarInfo.h"
#include "DamageObjectGenerator.h"
const float UpDownLaserFlyShip::addMoveValue = 0.05f;
const float UpDownLaserFlyShip::updownSpeed = 6.0f;
const float UpDownLaserFlyShip::setFirstPosY = 220.0f;

UpDownLaserFlyShip::UpDownLaserFlyShip()
    :LaserFlyShip()
{
    position.y = setFirstPosY;
}

UpDownLaserFlyShip::UpDownLaserFlyShip(VECTOR setPos, VECTOR setDestinationPos)
    :LaserFlyShip(setPos,setDestinationPos)
{
    position.y = setFirstPosY;
    GenerateLaser();
}

UpDownLaserFlyShip::~UpDownLaserFlyShip()
{
}

void UpDownLaserFlyShip::Update()
{
    totalMoveValue += addMoveValue;
    position.y += cosf(totalMoveValue) * updownSpeed;
    FiringObjOwner::Update(OwnerState::Move, position);
}

void UpDownLaserFlyShip::GenerateLaser()
{
    if (!isGenerateLaser)
    {
        ItemArgumentCarInfo itemInfo;
        itemInfo.SetCarInfo(this);
        DamageObjectGenerator::GenerateDamageObject(laser, itemInfo, this);
        isGenerateLaser = true;
    }
}
