#include "LaserFlyShip.h"
#include "DamageObjectGenerator.h"
#include "DirectionOfTravelGenerator.h"
#include "AssetManager.h"
#include "Utility.h"
const float LaserFlyShip::setFirstPosY = 400.0f;
const float LaserFlyShip::setModelSize = 0.2f;
const FlyShipArgumentInfo LaserFlyShip::setFlyShipParam
{
    8.0f,
    0.0f,
    35.0f,
    52.0f
};
LaserFlyShip::LaserFlyShip()
    :FlyShip(setFlyShipParam)
{
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle("Player/Rocker.mv1");
    MV1SetScale(modelHandle, { setModelSize,setModelSize,setModelSize });
    firstPosY = setFirstPosY;
    maxHeight = firstPosY;
    upSpeed = setFlyShipParam.addUpSpeed;
    minHeight = 300.0f;
    shipKInd = UFO;
    isGenerateLaser = false;
}

LaserFlyShip::LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos)
    :FlyShip(setFlyShipParam)
{
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle("Player/Rocker.mv1");
    MV1SetScale(modelHandle, { setModelSize,setModelSize,setModelSize });
    firstPosY = setFirstPosY;
    position = firstPos;
    position.y = firstPosY;
    maxHeight = firstPosY;
    upSpeed = setFlyShipParam.addUpSpeed;
    minHeight = 300.0f;
    destinationPosition = setDestinationPos;
    direction = VNorm(VSub(destinationPosition, VGet(position.x, destinationPosition.y, position.z)));
    shipKInd = UFO;
}

LaserFlyShip::~LaserFlyShip()
{
    SAFE_DELETE(aliveTimer);
}

void LaserFlyShip::Init(VECTOR newPosition, VECTOR newDestinationPos)
{
    position = newPosition;
    position.y = firstPosY;
    destinationPosition = newDestinationPos;
    destinationPosition.y = firstPosY;
    direction = VNorm(VSub(destinationPosition, position));
    firingPosition = position;
    ownerState = OwnerState::Stop;
    if (!isGenerateLaser)
    {
        ItemArgumentCarInfo itemInfo;
        itemInfo.SetCarInfo(this);
        DamageObjectGenerator::GenerateDamageObject(ufo, itemInfo, this);
        isGenerateLaser=true;
    }
}

void LaserFlyShip::Update(const float deltaTime)
{
}