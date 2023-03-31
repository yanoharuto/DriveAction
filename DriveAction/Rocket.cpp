#include "Rocket.h"
#include "EffectManager.h"
#include "AssetManager.h"
#include "EffekseerForDXLib.h"
#include "ConflictManager.h"
#include "Utility.h"
//���P�b�g�̃��f���̃A�h���X
 const std::string Rocket::rocketModelPass = "Item/Rocket/Rocket04_Grey.mv1";
//�G�t�F�N�g��model�̃A�h���X
 const std::string Rocket::effectPass = "bomb.efkefc";
//�������x
 const float Rocket::setFallingSpeed = 0.7f;
//�͂����Ԃ���
 const float Rocket::setBouncePower = 4.25f;
//�d��
 const float Rocket::gravityPower = 0.08f;
//���P�b�g�̃T�C�Y
 const float Rocket::setModelSize = 3.5f;
//�G�t�F�N�g�̃T�C�Y
 const float Rocket::setEffectSize = 22.000f;
//�����蔻��̑傫��
 const float Rocket::setRadius = 25.0f;
 //�R�������̓����蔻��̑傫��
 const float Rocket::setBurnRadius = 42.0f;
 
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="carInfo"></param>
Rocket::Rocket(ItemArgumentCarInfo carInfo)
{
    modelHandle = MV1DuplicateModel(AssetManager::GetDuplicate3DModelAssetHandle(rocketModelPass));
    MV1SetScale(modelHandle, VGet(setModelSize, setModelSize, setModelSize));
    fallingSpeed = setFallingSpeed;
    tag = ObjectTag::damageObject;
    radius = setRadius;
    position = carInfo.position;
    position = VAdd(position, VScale(VGet(0, -1, 0), carInfo.radius + radius));
    EffectManager::LoadEffectManager(effectPass, setEffectSize);
    velocity = VGet(0, 0, 0);
    direction = VGet(1, 0, 0);
    onGround = false;
    collider = new SphereCollider(this);
}

Rocket::~Rocket()
{
    StopEffekseer3DEffect(burnEffect);
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="deltaTime"></param>
void Rocket::Update()
{
    //�n�ʂɂԂ���O�͗����Ă���
    if (!onGround)
    {
        position.y -= fallingSpeed;
        fallingSpeed += fallingSpeed * gravityPower;
        //�n�ʂɂԂ��肻���ɂȂ�������G�t�F�N�g���o��
        if (position.y < 0.0f)
        {
            if (burnEffect == -1)
            {
                burnEffect = EffectManager::GetPlayEffect3D(effectPass);
                float positionY = position.y - radius;
                SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
                radius = setBurnRadius;
                onGround = true;
            }
        }
    }
    else
    {
        //�G�t�F�N�g��`�悵�I�������I��
        if (IsEffekseer3DEffectPlaying(burnEffect) == -1)
        {
            aliveFlag = false;
            burnEffect = -1;
        }
    }
}
/// <summary>
/// �Փˌ�̏���
/// </summary>
void Rocket::ConflictProccess(ConflictExamineResultInfo resultInfo)
{
    if (resultInfo.tag != ObjectTag::damageObject)
    {
        if (burnEffect==-1)
        {
            //�_���[�W����̂���I�u�W�F�N�g�ȊO�ɏՓˌ�G�t�F�N�g���o��
            burnEffect = EffectManager::GetPlayEffect3D(effectPass);
            float positionY = position.y - radius;
            SetPosPlayingEffekseer3DEffect(burnEffect, position.x, positionY, position.z);
            //�����蔻��𔚔��Ɠ������炢�ɂ���
            radius = setBurnRadius;
            onGround = true;
        }
    }
}