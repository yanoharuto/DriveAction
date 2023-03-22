#include "DamageImpact.h"
#include "AssetManager.h"



DamageImpact::DamageImpact()
{
}

DamageImpact::DamageImpact(ItemArgumentCarInfo carInfo)
{
    radius = setRadius;
    direction = carInfo.direction;
    position = VAdd(carInfo.position, VScale(direction,setCarBetween + carInfo.radius + setRadius + VSize(carInfo.velocity)));
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle(assetAddress);
    velocity = VScale(direction, speed);
    aliveTime = setAliveTime;
    tag = ObjectTag::damageObject;
}

DamageImpact::~DamageImpact()
{
    
}

void DamageImpact::Update(float deltaTime)
{
    aliveTime -= deltaTime;
    if (aliveTime > 0)
    {
        position = VAdd(position, VScale(velocity, deltaTime));
        UpdateMV1Pos();
    }
    else
    {
        aliveFlag = false;
    }
}

void DamageImpact::ConflictProccess(const ConflictExamineResultInfo conflictInfo)
{
    aliveFlag = false;
}
