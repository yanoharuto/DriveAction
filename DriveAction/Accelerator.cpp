#include "Accelerator.h"

Accelerator::Accelerator()
{
    effecacyTime = setEffecacyTime;
    itemTag = ItemTag::accelerator;
}

Accelerator::~Accelerator()
{
}

void Accelerator::Update(float deltaTime,ItemArgumentCarInfo carInfo)
{
    if (useSituation == ItemUseSituation::Useing)
    {
        effecacyValue += addEffecacyValue * deltaTime;
        effecacyTime -= deltaTime;
        if (effecacyTime < 0)
        {
            useSituation = ItemUseSituation::DoneUsing;
        }
    }
}
