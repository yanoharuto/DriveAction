#pragma once
#include "Item.h"
/// <summary>
/// 加速効果がメインのアイテム
/// </summary>
class Accelerator :
    public ItemBase
{
public:
    Accelerator();
    ~Accelerator();

    /// <summary>
    /// 加速量の更新
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="carInfo"></param>
    void Update(float deltaTime,ItemArgumentCarInfo carInfo)override;
private:
    const float addEffecacyValue = 38.5f;
    const float setEffecacyTime = 1.8f;
};