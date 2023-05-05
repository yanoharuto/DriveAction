#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "AssetManager.h"
#include "SoundPlayer.h"
#include "Car.h"
#include "FlyShipArgumentInfo.h"
#include "Timer.h"
const int BomberFlyShip:: SEVolume = 80;
//速さ
const float BomberFlyShip::speed = 5.8f;
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


BomberFlyShip::BomberFlyShip(VECTOR setFirstPos,VECTOR setDestinationPos)
    :FlyShip(Init::bomberShip)
{   
    setFirstPos.y = position.y;
    setDestinationPos.y = position.y;
    position = setFirstPos;
    direction = VNorm(VSub(setDestinationPos, position));
    direction.y = 0;
    timer = new Timer(setFlyShipParam.setCoolTime);
    SoundPlayer::LoadSound(flightSE);
    SoundPlayer::Play3DSE(flightSE);
    SoundPlayer::SetPosition3DSound(position, flightSE);
}

void BomberFlyShip::Update()
{
    velocity = VScale(direction, speed);

    //クールタイムが終わったら
    if (timer->IsOverLimitTime())
    {
        //爆弾を投下
        DamageObjectGenerator::GenerateDamageObject(Item::bomber,sub);
        timer->Init();
    }
    UpdateMV1Pos();
    ModelSetMatrix();
}

