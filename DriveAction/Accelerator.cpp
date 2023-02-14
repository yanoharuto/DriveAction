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
        SetPosPlayingEffekseer3DEffect(playEffect, carInfo.position.x, carInfo.position.y, carInfo.position.z);
        float rota = VDot(VGet(1, 0, 0), carInfo.direction);
        SetRotationPlayingEffekseer3DEffect(playEffect, 0, acosf(rota), 0);
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
    if (useSituation != ItemUseSituation::DoneUsing)
    {
        playEffect = IsEffekseer3DEffectPlaying(effectResource);
        SetPosPlayingEffekseer3DEffect(playEffect, carInfo.position.x, carInfo.position.y, carInfo.position.z);
        useSituation = ItemUseSituation::Useing;
    }
}