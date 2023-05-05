#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "AssetManager.h"
#include "SoundPlayer.h"
#include "Car.h"
#include "FlyShipArgumentInfo.h"
#include "Timer.h"
const int BomberFlyShip:: SEVolume = 80;
//����
const float BomberFlyShip::speed = 5.8f;
//����Ԏ��̌��ʉ�
const std::string BomberFlyShip::flightSE = "space-fighter-taking-off-1.mp3";
//�������ԁ@���e���˃N�[���^�C���@�ő卂�x�@�㏸���x
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

    //�N�[���^�C�����I�������
    if (timer->IsOverLimitTime())
    {
        //���e�𓊉�
        DamageObjectGenerator::GenerateDamageObject(Item::bomber,sub);
        timer->Init();
    }
    UpdateMV1Pos();
    ModelSetMatrix();
}

