#include "LaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include "DirectionOfTravelGenerator.h"
#include "AssetManager.h"
#include "Utility.h"

LaserFlyShip::LaserFlyShip()
{
    modelHandle = AssetManager::Get3DModelAssetHandle("Player/Rocker.mv1");
}
/// <summary>
/// レーザーを発射する飛行船
/// </summary>
/// <param name="firstPos"></param>
/// <param name="setDestinationPos"></param>
LaserFlyShip::LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos)
{
    modelHandle = AssetManager::Get3DModelAssetHandle("Player/Rocker.mv1");

    position = firstPos;
    firstPosY = position.y;
    direction = VNorm(VSub(setDestinationPos, VGet(position.x, setDestinationPos.y, position.z)));

    firingPosition = position;
    ownerState = OwnerState::Delete;

}

LaserFlyShip::~LaserFlyShip()
{
}
/// <summary>
/// カメラの視界に入らなくなったらエフェクトを消す
/// </summary>
/// <param name="playerInfo"></param>
void LaserFlyShip::Init(PlayerRelatedInfo playerInfo)
{
    VECTOR between = VSub(position, playerInfo.objInfo.pos);
    float degree = OriginalMath::GetDegreeMisalignment(between, playerInfo.objInfo.dir);

    if (degree < 90)
    {
        ownerState = OwnerState::Move;
    }
    else
    {
        ownerState = OwnerState::Delete;
    }
}
