#pragma once
#include <string>
#include "Item.h"
/// <summary>
/// 加速効果のアイテム
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
    void Draw();
    void ShowEffect(ItemArgumentCarInfo carInfo)override;
    
private:
    int effectResource=-1;
    int playEffect = -1;
    const std::string effectAddress = "wind.efkefc";
    const float addEffecacyValue = 38.5f;
    const float setEffecacyTime = 1.8f;
};