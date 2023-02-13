#pragma once
#include "Item.h"
/// <summary>
/// �������ʂ����C���̃A�C�e��
/// </summary>
class Accelerator :
    public ItemBase
{
public:
    Accelerator();
    ~Accelerator();

    /// <summary>
    /// �����ʂ̍X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="carInfo"></param>
    void Update(float deltaTime,ItemArgumentCarInfo carInfo)override;
private:
    const float addEffecacyValue = 38.5f;
    const float setEffecacyTime = 1.8f;
};