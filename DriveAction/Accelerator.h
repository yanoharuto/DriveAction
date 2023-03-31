#pragma once
#include <string>
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
    void Update(ItemArgumentCarInfo carInfo)override;
    void Draw();
    void ShowEffect(ItemArgumentCarInfo carInfo)override;
    
private:
    int effectResource=-1;
    int playEffect = -1;
    const std::string effectPass = "wind.efkefc";
    const float addEffecacyValue = 62.5f;
    const float setEffecacyTime = 1.8f;
};