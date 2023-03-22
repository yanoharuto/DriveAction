#pragma once
#include <string>
#include "ItemTag.h"
#include "FiringObjOwner.h"
#include "ItemArgumentCarInfo.h"

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
    ~DamageObjectGenerator();
    /// <summary>
    /// アイテムの種類によって生成するアイテムを変更する
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="carInfo"></param>
    static Actor* GenerateDamageObject(ItemTag itemTag, ItemArgumentCarInfo carInfo,FiringObjOwner* owner);
};