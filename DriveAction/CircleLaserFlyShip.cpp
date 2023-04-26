#include "CircleLaserFlyShip.h"
#include "AssetManager.h"
#include "DamageObjectGenerator.h"
//�����ʒu
const float CircleLaserFlyShip::setFirstPosY = 400.0f;
//model�̑傫��
const float CircleLaserFlyShip::setModelSize = 0.3f;

/// <summary>
/// �~��ɐw�`���������s�D
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
