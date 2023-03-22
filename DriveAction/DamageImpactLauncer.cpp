#include "DamageImpactLauncer.h"
#include "DamageObjectGenerator.h"
DamageImpactLauncher::DamageImpactLauncher()
{
    effecacyTime = setEffecacyTime;
    itemTag =ItemTag::ufo;
}

DamageImpactLauncher::~DamageImpactLauncher()
{
}

void DamageImpactLauncher::Update(float deltaTime, ItemArgumentCarInfo carInfo)
{

}

void DamageImpactLauncher::ShowEffect(ItemArgumentCarInfo carInfo)
{
    if (useSituation != ItemUseSituation::DoneUsing)
    {
        useSituation = ItemUseSituation::DoneUsing;
    }
}
