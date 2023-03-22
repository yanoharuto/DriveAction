#pragma once
#include <string>
#include "ConflictProcesser.h"
#include "AssetManager.h"
#include "FiringItemManager.h"
#include "ItemTag.h"
/// <summary>
/// 投擲アイテムなどのダメージがあるオブジェクトを生成する
/// </summary>
class DamageObjectGenerator
{
public:
    /// <summary>
    /// デフォルトコンストラクタ
    /// </summary>
    DamageObjectGenerator();
    /// <summary>
    /// ポインタを貰う
    /// </summary>
    /// <param name="conflictPro"></param>
    /// <param name="assetMana"></param>
    /// <param name="firingItemMana"></param>
    DamageObjectGenerator(ConflictProcesser* conflictPro, FiringItemManager* firingItemMana);
    ~DamageObjectGenerator();
    /// <summary>
    /// アイテムの種類によって生成するアイテムを変更する
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="carInfo"></param>
    static void GenerateDamageObject(ItemTag itemTag, ItemArgumentCarInfo carInfo);
private:
};

