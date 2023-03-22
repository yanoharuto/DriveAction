#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "AssetManager.h"
//初期Y座標
const float BomberFlyShip:: setFirstPosY = 700.0f;
//速さ
const float BomberFlyShip:: speed = 390.0f;
//modelの大きさ
const float BomberFlyShip::modelSize = 0.4f;
//幅
const float BomberFlyShip::setRadius = 12.0f;
//生存時間　爆弾発射クールタイム　最大高度　上昇速度
const FlyShipArgumentInfo BomberFlyShip::setFlyShipParam
{
    4.0f,
    0.3f,
    220.0f,
    12.0f
};
BomberFlyShip::BomberFlyShip()
    :FlyShip(setFlyShipParam)
{
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle("Player/PrototypeZero.mv1");
    MV1SetScale(modelHandle, { modelSize,modelSize,modelSize });
    firstPosY = setFirstPosY;
    coolTime = setCoolTime;
    radius = setRadius;
    shipKInd = Bomber;
    aliveFlag = false;
}

BomberFlyShip::BomberFlyShip(VECTOR setFirstPos,VECTOR setDestinationPos)
    :FlyShip(setFlyShipParam)
{
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle("Player/PrototypeZero.mv1");
    MV1SetScale(modelHandle, {modelSize,modelSize,modelSize });
    firstPosY = setFirstPosY;
    position = setFirstPos;
    position.y = firstPosY;
    destinationPosition = setDestinationPos;
    destinationPosition.y = firstPosY;
    direction = VNorm(VSub(destinationPosition, position));
    coolTime = setCoolTime;
    radius = setRadius;
    shipKInd = Bomber;
    aliveFlag = false;
}

BomberFlyShip::~BomberFlyShip()
{
    SAFE_DELETE(aliveTimer);
}

void BomberFlyShip::Update(const float deltaTime)
{
    velocity = VScale(direction, speed * deltaTime);
    coolTime -= deltaTime;
    //時間経過したら消える
    if (aliveTimer->IsOverLimitTime())
    {
        aliveFlag = false;
    }
    //クールタイムが終わったら
    else if (coolTime < 0)
    {
        coolTime = setCoolTime;
        //投下位置設定
        ItemArgumentCarInfo itemInfo = {};
        itemInfo.SetCarInfo(this);
        itemInfo.position = position;
        itemInfo.position.y -= radius;
        //爆弾を投下
        DamageObjectGenerator::GenerateDamageObject(bomber,itemInfo,this);
        bomberCount++;
    }
    UpdateMV1Pos();
    ModelSetMatrix();
}