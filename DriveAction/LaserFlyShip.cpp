#include "LaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include "AssetManager.h"
#include "Utility.h"
#include "OriginalMath.h"
/// <summary>
/// ���[�U�[�𔭎˂����s�D
/// </summary>
/// <param name="firstPos"></param>
/// <param name="setDestinationPos"></param>
LaserFlyShip::LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos,Init::InitObjKind kind)
    :FlyShip(kind)
{
    position = firstPos;
    firstPosY = position.y;
    direction = VNorm(VSub(setDestinationPos, VGet(position.x, setDestinationPos.y, position.z)));
}