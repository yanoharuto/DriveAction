#pragma once
#include "Item.h"
/// <summary>
/// �Ռ��g���˃A�C�e��
/// </summary>
class DamageImpactLauncher :
    public ItemBase
{
public:
    DamageImpactLauncher();
    ~DamageImpactLauncher();
    void Update(float deltaTime, ItemArgumentCarInfo carInfo)override;
    void ShowEffect(ItemArgumentCarInfo carInfo)override;
private:
    const float setEffecacyTime = 4.2f;
};

