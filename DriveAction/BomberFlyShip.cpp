#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "AssetManager.h"
#include "SoundPlayer.h"
#include "Car.h"
const int BomberFlyShip:: SEVolume = 80;
//����Y���W
const float BomberFlyShip:: setFirstPosY = 500.0f;
//����
const float BomberFlyShip:: speed = 5.8f;
//model�̑傫��
const float BomberFlyShip::modelSize = 0.7f;
//��
const float BomberFlyShip::setRadius = 12.0f;
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
    //�N�[���^�C�����I�������
    if (coolTime < 0)
    {
        coolTime = setFlyShipParam.setCoolTime;
        //�����ʒu�ݒ�
        ItemArgumentCarInfo itemInfo = {};
        itemInfo.SetCarInfo(this);
        itemInfo.position = position;
        itemInfo.position.y -= radius;
        //���e�𓊉�
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
