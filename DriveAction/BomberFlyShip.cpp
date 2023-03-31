#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "AssetManager.h"
#include "SoundPlayer.h"
#include "Car.h"
const int BomberFlyShip:: SEVolume = 80;
//初期Y座標
const float BomberFlyShip:: setFirstPosY = 500.0f;
//速さ
const float BomberFlyShip:: speed = 5.8f;
//modelの大きさ
const float BomberFlyShip::modelSize = 0.7f;
//幅
const float BomberFlyShip::setRadius = 12.0f;
//空を飛ぶ時の効果音
const std::string BomberFlyShip::flightSE = "space-fighter-taking-off-1.mp3";
//生存時間　爆弾発射クールタイム　最大高度　上昇速度
const FlyShipArgumentInfo BomberFlyShip::setFlyShipParam
{
    4.0f,
    0.3f,
    220.0f,
    12.0f
};
BomberFlyShip::BomberFlyShip()
{
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle("Player/PrototypeZero.mv1");
    MV1SetScale(modelHandle, { modelSize,modelSize,modelSize });
    coolTime = setFlyShipParam.setCoolTime;
    radius = setRadius;
    aliveFlag = false;
    SoundPlayer::LoadSound(flightSE);
    SoundPlayer::SetSoundVolume(50,flightSE);
}

BomberFlyShip::BomberFlyShip(VECTOR setFirstPos,VECTOR setDestinationPos)
{
    modelHandle = AssetManager::GetDuplicate3DModelAssetHandle("Player/PrototypeZero.mv1");
    MV1SetScale(modelHandle, {modelSize,modelSize,modelSize });
    position = setFirstPos;
    position.y = setFlyShipParam.setCoolTime;;
    direction = VNorm(VSub(setDestinationPos, position));
    direction.y = 0;
    coolTime = setFlyShipParam.setCoolTime;
    radius = setRadius;
    aliveFlag = false;
    SoundPlayer::LoadSound(flightSE);
}

BomberFlyShip::~BomberFlyShip()
{
}

void BomberFlyShip::Update()
{
    velocity = VScale(direction, speed);
    coolTime -= DELTATIME;
    position.y = setFirstPosY;
    //クールタイムが終わったら
    if (coolTime < 0)
    {
        coolTime = setFlyShipParam.setCoolTime;
        //投下位置設定
        ItemArgumentCarInfo itemInfo = {};
        itemInfo.SetCarInfo(this);
        itemInfo.position = position;
        itemInfo.position.y -= radius;
        //爆弾を投下
        DamageObjectGenerator::GenerateDamageObject(bomber,itemInfo,this);
        
    }
    UpdateMV1Pos();
    ModelSetMatrix();
}

void BomberFlyShip::Init(VECTOR newPosition, VECTOR newDestinationPos)
{
    position = newPosition;
    position.y = setFirstPosY;
    direction = VNorm(VSub(newDestinationPos, newPosition));
    direction.y = 0;
    aliveFlag = true;
    SoundPlayer::Play3DSE(flightSE);
    SoundPlayer::SetPosition3DSound(position, flightSE);
}
