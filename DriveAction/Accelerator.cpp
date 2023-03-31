#include "Accelerator.h"
#include "OriginalMath.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "Utility.h"
Accelerator::Accelerator()
{
    effecacyTime = setEffecacyTime;
    itemTag = ItemTag::bomber;
    EffectManager::LoadEffectManager(effectPass, 30.0f);

}

Accelerator::~Accelerator()
{
    StopEffekseer3DEffect(playEffect);
    DeleteEffekseerEffect(playEffect);
}

void Accelerator::Update(ItemArgumentCarInfo carInfo)
{
    if (useSituation == ItemUseSituation::Useing)
    {
        effecacyValue += addEffecacyValue;
        effecacyTime -= DELTATIME;
        //エフェクトの位置変更
        VECTOR pos = VAdd(carInfo.position, VScale(carInfo.direction, carInfo.radius));
        SetPosPlayingEffekseer3DEffect(playEffect, pos.x, pos.y, pos.z);
        //車の向きに合わせる
        float rota = VDot(VNorm(VGet(1, 0, 0)), VNorm(carInfo.direction));
        SetRotationPlayingEffekseer3DEffect(playEffect, 0, acosf(rota) * RAGE, 0);
        //加速し終わったら
        if (effecacyTime < 0)
        {
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
        playEffect = EffectManager::GetPlayEffect3D(effectPass);
        SetPosPlayingEffekseer3DEffect(playEffect, carInfo.position.x, carInfo.position.y, carInfo.position.z);
        useSituation = ItemUseSituation::Useing;
    }
}