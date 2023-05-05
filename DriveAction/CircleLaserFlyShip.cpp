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
    :LaserFlyShip(firstPos, setDestinationPos,Init::circleLaserShip)
{
    modelSize = setModelSize;
    firstPosY = setFirstPosY;
    position.y = firstPosY;
    GenerateLaser();
}

void CircleLaserFlyShip::GenerateLaser()
{
    DamageObjectGenerator::GenerateDamageObject(Item::littleRadLaser, sub);
}
