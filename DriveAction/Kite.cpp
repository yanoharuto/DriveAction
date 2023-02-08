#include "Kite.h"

Kite::Kite()
{
	effecacyTime = setEffecacyTime;
	itemTag = kite;
}

Kite::~Kite()
{
}

void Kite::Update(float deltaTime)
{
	if (useSituation == ItemUseSituation::Useing)
	{
 		effecacyTime -= deltaTime;
		if (coolTime < -0.1f)
		{
			coolTime = setCoolTime;
		}
		else
		{
			coolTime -= deltaTime;
		}
		effecacyValue = effecacyValue < maxHeight ?  effecacyValue + flyPower * deltaTime: maxHeight ;
		//Žg‚¢Ø‚Á‚½
		if (effecacyTime < 0)
		{
			useSituation = ItemUseSituation::DoneUsing;
		}
	}
}
void Kite::ShowEffect()
{
	if (useSituation != ItemUseSituation::DoneUsing)
	{
		useSituation = ItemUseSituation::Useing;
	}
}