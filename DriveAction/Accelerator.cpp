#include "Accelerator.h"
#include "EffekseerForDXLib.h"
Accelerator::Accelerator()
{
    effecacyTime = setEffecacyTime;
    itemTag = ItemTag::accelerator;
    effectResource = LoadEffekseerEffect(address.c_str(), 30.0f);
}

Accelerator::~Accelerator()
{
    DeleteEffekseerEffect(effectResource);
}

void Accelerator::Update(float deltaTime,ItemArgumentCarInfo carInfo)
{
    if (useSituation == ItemUseSituation::Useing)
    {
        effecacyValue += addEffecacyValue * deltaTime;
        effecacyTime -= deltaTime;
        VECTOR pos = VAdd(carInfo.position, VScale(carInfo.direction, carInfo.radius));
        SetPosPlayingEffekseer3DEffect(playEffect, pos.x, pos.y, pos.z);
        float rota = VDot(VNorm(VGet(1, 0, 0)), VNorm(carInfo.direction));
        //SetRotationPlayingEffekseer3DEffect(playEffect, 0, acosf(rota), 0);
        if (effecacyTime < 0)
        {
            StopEffekseer3DEffect(playEffect);
            useSituation = ItemUseSituation::DoneUsing;
        }
    }
}

void Accelerator::Draw()
{
}

void Accelerator::ShowEffect(ItemArgumentCarInfo carInfo)
{
    if (useSituation == ItemUseSituation::nonUse)
    {
        playEffect = IsEffekseer3DEffectPlaying(effectResource);
        SetPosPlayingEffekseer3DEffect(playEffect, carInfo.position.x, carInfo.position.y, carInfo.position.z);
        useSituation = ItemUseSituation::Useing;
    }
}