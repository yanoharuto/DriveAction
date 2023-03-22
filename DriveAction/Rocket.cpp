#include "Rocket.h"
#include "EffectManager.h"
#include "AssetManager.h"
#include "EffekseerForDXLib.h"
#include "ConflictManager.h"
#include "Utility.h"
//���P�b�g�̃��f���̃A�h���X
 const std::string Rocket::rocketModelAddress = "Item/Rocket/Rocket04_Grey.mv1";
//�G�t�F�N�g��model�̃A�h���X
 const std::string Rocket::effectAddress = "bomb.efkefc";
//�������x
 const float Rocket::setFallingSpeed = 350.0f;
//�͂����Ԃ���
 const float Rocket::setBouncePower = 4.25f;
//�d��
 const float Rocket::gravityPower = 0.98f;
//���P�b�g�̃T�C�Y
 const float Rocket::setModelSize = 3.5f;
//�G�t�F�N�g�̃T�C�Y
 const float Rocket::setEffectSize = 22.000f;
//�����蔻��̑傫��
 const float Rocket::setRadius = 34.0f;
 //�R�������̓����蔻��̑傫��
 const float Rocket::setBurnRadius = 58.0f;
 
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="carInfo"></param>
Rocket::Rocket(ItemArgumentCarInfo carInfo)
{
    modelHandle = MV1DuplicateModel(AssetManager::GetDuplicate3DModelAssetHandle(rocketModelAddress));
    MV1SetScale(modelHandle, VGet(setModelSize, setModelSize, setModelSize));
    fallingSpeed = setFallingSpeed;
    tag = ObjectTag::damageObject;
    bouncePower = setBouncePower;
    radius = setRadius;
    position = carInfo.position;
    position = VAdd(position, VScale(VGet(0, -1, 0), carInfo.radius + radius));
    EffectManager::LoadEffectManager(effectAddress, setEffectSize);
    velocity = VGet(0, 0, 0);
    direction = VGet(1, 0, 0);
    onGround = false;
    collider = new SphereCollider(this);
}

Rocket::~Rocket()
{
    StopEffekseer3DEffect(playEffect);
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="deltaTime"></param>
void Rocket::Update(float deltaTime)
{
    if (!onGround)
    {
        position.y -= fallingSpeed * deltaTime;
        fallingSpeed += fallingSpeed * gravityPower * deltaTime;
    }
    else
    {
        //�G�t�F�N�g��`�悵�I�������
        if (IsEffekseer3DEffectPlaying(playEffect) == -1)
        {
            aliveFlag = false;
        }
    }
}
/// <summary>
/// �Փˌ�̏���
/// </summary>
void Rocket::ConflictProccess(ConflictExamineResultInfo resultInfo)
{
    if (!onGround&&resultInfo.tag!=ObjectTag::damageObject)
    {
        playEffect = EffectManager::GetPlayEffect3D(effectAddress);
        float positionY = position.y - radius;
        SetPosPlayingEffekseer3DEffect(playEffect, position.x, positionY, position.z);
        radius = setBurnRadius;
        onGround = true;
    }
}