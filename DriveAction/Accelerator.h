#pragma once
#include "Item.h"
/// <summary>
/// �������ʂ����C���̃A�C�e��
/// </summary>
class Accelerator :
    public Item
{
public:
    Accelerator();
    ~Accelerator();
    void Update(float deltaTime)override;
    void ShowEffect()override;
private:
    const float addEffecacyValue = 38.5f;
    const float setEffecacyTime = 1.8f;
};