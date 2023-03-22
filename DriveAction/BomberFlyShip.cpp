#include "BomberFlyShip.h"
#include "DamageObjectGenerator.h"
#include "Utility.h"
#include "AssetManager.h"
//����Y���W
const float BomberFlyShip:: setFirstPosY = 700.0f;
//����
const float BomberFlyShip:: speed = 390.0f;
//model�̑傫��
const float BomberFlyShip::modelSize = 0.4f;
//��
const float BomberFlyShip::setRadius = 12.0f;
//�������ԁ@���e���˃N�[���^�C���@�ő卂�x�@�㏸���x
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
    //���Ԍo�߂����������
    if (aliveTimer->IsOverLimitTime())
    {
        aliveFlag = false;
    }
    //�N�[���^�C�����I�������
    else if (coolTime < 0)
    {
        coolTime = setCoolTime;
        //�����ʒu�ݒ�
        ItemArgumentCarInfo itemInfo = {};
        itemInfo.SetCarInfo(this);
        itemInfo.position = position;
        itemInfo.position.y -= radius;
        //���e�𓊉�
        DamageObjectGenerator::GenerateDamageObject(bomber,itemInfo,this);
        bomberCount++;
    }
    UpdateMV1Pos();
    ModelSetMatrix();
}