#include "UpDownLaserFlyShip.h"
#include "ItemArgumentCarInfo.h"
#include "DamageObjectGenerator.h"

const float UpDownLaserFlyShip::addMoveValue = 0.05f;
const float UpDownLaserFlyShip::updownSpeed = 6.0f;

UpDownLaserFlyShip::UpDownLaserFlyShip(VECTOR setPos, VECTOR setDestinationPos)
    :LaserFlyShip(setPos,setDestinationPos,Init::upDownLaserShip)
{
    setPos.y = position.y;
    position = setPos;
    GenerateLaser();
}

void UpDownLaserFlyShip::Update()
{
    totalMoveValue += addMoveValue;
    position.y += cosf(totalMoveValue) * updownSpeed;
}

void UpDownLaserFlyShip::GenerateLaser()
{
    DamageObjectGenerator::GenerateDamageObject(Item::bigRadLaser, sub);
}
