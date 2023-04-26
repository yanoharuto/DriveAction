#include "CircleLaserFlyShip.h"
#include "AssetManager.h"
#include "DamageObjectGenerator.h"
//初期位置
const float CircleLaserFlyShip::setFirstPosY = 400.0f;
//modelの大きさ
const float CircleLaserFlyShip::setModelSize = 0.3f;

/// <summary>
/// 円状に陣形を作った飛行船
/// </summary>
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
    ItemArgumentCarInfo itemInfo;
    itemInfo.SetCarInfo(this);
    DamageObjectGenerator::GenerateDamageObject(ufo, itemInfo, this);
}
