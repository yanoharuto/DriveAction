#include "CircleLaserFlyShip.h"
#include "AssetManager.h"
#include "DamageObjectGenerator.h"
const float CircleLaserFlyShip::setFirstPosY = 400.0f;
const float CircleLaserFlyShip::setModelSize = 0.3f;
CircleLaserFlyShip::CircleLaserFlyShip()
{
}

CircleLaserFlyShip::CircleLaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos)
    :LaserFlyShip(firstPos, setDestinationPos)
{
    modelSize = setModelSize;
    firstPosY = setFirstPosY;
    position.y = firstPosY;
    firingPosition = position;
    GenerateLaser();
}

void CircleLaserFlyShip::GenerateLaser()
{
    if (!isGenerateLaser)
    {
        ItemArgumentCarInfo itemInfo;
        itemInfo.SetCarInfo(this);
        DamageObjectGenerator::GenerateDamageObject(ufo, itemInfo, this);
        isGenerateLaser = true;
    }
}
