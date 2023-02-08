#pragma once
#include "Item.h"
class DamageImpact :
    public Item
{
public:
    DamageImpact();
    ~DamageImpact();
    void Update(float deltaTime)override;
    void ShowEffect( )override;
private:
    const float setEffecacyTime = 4.2f;
    const float setCoolTime = 0.8f;
};

