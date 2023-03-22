#include "Rocket.h"
#include "EffectManager.h"
#include "AssetManager.h"
#include "EffekseerForDXLib.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="carInfo"></param>
Rocket::Rocket(ItemArgumentCarInfo carInfo)
{
    position = carInfo.position;
    position = VAdd(position, VScale(carInfo.direction, -20));
    modelHandle = MV1DuplicateModel(AssetManager::GetDuplicate3DModelAssetHandle(rocketModelAddress));
    MV1SetScale(modelHandle, VGet(setSize, setSize, setSize));
    tag = ObjectTag::damageObject;
    bouncePower = setBouncePower;
    radius = setRadius;
    EffectManager::LoadEffectManager(effectAddress, 1.0f);
    onGround = false;

}

Rocket::~Rocket()
{
    MV1DeleteModel(modelHandle);
    DeleteEffekseerEffect(playEffect);
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
        MV1SetPosition(modelHandle, position);
        fallingSpeed += fallingSpeed * gravityPower * deltaTime;
    }
    else
    {
        if (!IsEffekseer3DEffectPlaying(playEffect))
        {
            aliveFlag = false;
        }
    }
}
/// <summary>
/// �Փˌ�̏���
/// </summary>
void Rocket::ConflictProccess()
{
    onGround = true;
    playEffect = EffectManager::GetPlayEffect3D(effectAddress);
    SetPosPlayingEffekseer3DEffect(playEffect, position.x, position.y, position.z);
}