#pragma once
#include "Item.h"
#include "ConflictProcesser.h"
#include "DamageObjectGenerator.h"
/// <summary>
/// アイテムを生成して使えるようにする
/// </summary>
class ItemHolder
{
public:
    ItemHolder();
    ~ItemHolder();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="damageObjeGene"></param>
    /// <param name="carInfo"></param>
    /// <param name="deltaTime"></param>
    void Update(DamageObjectGenerator* damageObjeGene,ItemArgumentCarInfo carInfo,float deltaTime);
    /// <summary>
    /// アイテムを所得
    /// </summary>
    /// <param name="rank"></param>
    void SelectItem(int rank);
    /// <summary>
    /// アイテムを使用
    /// </summary>
    void UseItem(ItemArgumentCarInfo carInfo);
    /// <summary>
    /// アイテムの描画
    /// </summary>
    void ItemDraw();
    /// <summary>
    /// アイテムの情報を渡す
    /// </summary>
    /// <returns>何もアイテムを持ってないならTagはnon</returns>
    ItemInfo GetItemInfo();

private:
    ItemBase* item;
    float rouletteTime = -1;
    const float setRouletteTime = 2.5f;
    bool roulette = false;
};