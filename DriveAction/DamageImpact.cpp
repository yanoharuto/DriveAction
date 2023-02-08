#include "DamageImpact.h"

DamageImpact::DamageImpact()
{
    effecacyTime = setEffecacyTime;
}

DamageImpact::~DamageImpact()
{
}

void DamageImpact::Update(float deltaTime)
{
}

void DamageImpact::ShowEffect()
{
	if (useSituation != ItemUseSituation::DoneUsing)
	{
		useSituation = ItemUseSituation::Useing;
		if (coolTime < 0)
		{
			coolTime = setCoolTime;
		}
	}
}
