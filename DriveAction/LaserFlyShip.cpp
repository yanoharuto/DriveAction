#include "LaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include "DirectionOfTravelGenerator.h"
#include "AssetManager.h"
#include "Utility.h"

const float LaserFlyShip::deleteBetween = 1500.0f;

LaserFlyShip::LaserFlyShip()
{
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle("Player/Rocker.mv1");

    isGenerateLaser = false;
}

LaserFlyShip::LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos)
{
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle("Player/Rocker.mv1");

    position = firstPos;
    
    direction = VNorm(VSub(setDestinationPos, VGet(position.x, setDestinationPos.y, position.z)));

    firingPosition = position;
    ownerState = OwnerState::Delete;

}

LaserFlyShip::~LaserFlyShip()
{
}

void LaserFlyShip::Init(VECTOR playerPos)
{
    float between = VSize(VSub(playerPos,position));
    if (between > deleteBetween)
    {
        ownerState = OwnerState::Delete;
    }
    else
    {
        ownerState = OwnerState::Move;
    }
}
