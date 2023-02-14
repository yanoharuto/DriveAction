#pragma once
#include "Item.h"
/// <summary>
/// �������ʂ̃A�C�e��
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
    void Draw();
    void ShowEffect(ItemArgumentCarInfo carInfo)override;
    
private:
    int effectResource=-1;
    int playEffect = -1;
    const std::string address = "data/effect/accelation.efkefc";
    const float addEffecacyValue = 38.5f;
    const float setEffecacyTime = 1.8f;
};