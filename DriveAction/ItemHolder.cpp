#include<iostream>
#include "OriginalMath.h"
#include "ItemHolder.h"
#include "Kite.h"
#include "Accelerator.h"
#include "DamageImpactLauncer.h"
#include "Utility.h"

ItemHolder::ItemHolder()
{
    item = nullptr;
}

ItemHolder::~ItemHolder()
{
    SAFE_DELETE(item);
}
/// <summary>
/// 更新
/// </summary>
/// <param name="damageObjeGene"></param>
/// <param name="carInfo"></param>
/// <param name="deltaTime"></param>
void ItemHolder::Update(DamageObjectGenerator* damageObjeGene,ItemArgumentCarInfo carInfo,float deltaTime)
{
    rouletteTime -= deltaTime;
    if (rouletteTime < 0)
    {
        roulette = false;
    }

    if (item != nullptr && !roulette) 
    {
        //アイテムの情報を所得
        ItemInfo itemInfo = item->GetItemInfo();
        //アイテムの使用状況
        switch (itemInfo.itemSituation)
        {
        case ItemUseSituation::Useing:
            //アイテムの効果を更新
            item->Update(deltaTime,carInfo);
            break;
        case ItemUseSituation::DoneUsing://アイテムを使い終わったら
            SAFE_DELETE(item);
            break;
        default:
            break;
        }
        
    }
}
/// <summary>
/// アイテムを所得
/// </summary>
/// <param name="rank"></param>
void ItemHolder::SelectItem(int rank)
{
    if (!roulette && item == nullptr)
    {
        roulette = true;
        rouletteTime = setRouletteTime;
        switch (OriginalMath::GetRandom(1,rank))
        {
        case 1:
            item = new DamageImpactLauncher();
            break;
        case 2:
            item = new Accelerator();
            break;
        case 3:
        case 4:
            item = new Kite();
            break;
        }

    }
}
/// <summary>
/// アイテムを使用
/// </summary>
void ItemHolder::UseItem(ItemArgumentCarInfo carInfo)
{
    if (item != nullptr && !roulette)
    {
        item->ShowEffect(carInfo);
    }
}
/// <summary>
/// アイテムの描画
/// </summary>
void ItemHolder::ItemDraw()
{
    if (item != nullptr && !roulette)
    {
        if (item->GetItemInfo().itemSituation == ItemUseSituation::Useing)
        {
            item->Draw();
        }
    }
}
/// <summary>
/// アイテムの情報を渡す
/// </summary>
/// <returns>何もアイテムを持ってないならTagはnon</returns>
ItemInfo ItemHolder::GetItemInfo()
{
    if (item != nullptr && !roulette)
    {
        return item->GetItemInfo();
    }
    else if (roulette)
    {
        ItemInfo itemInfo = {};
        itemInfo.itemTag = ItemTag::roulette;
        return itemInfo;
    }
    else
    {
        //何もアイテムを持ってないならTagはnon
        ItemInfo itemInfo = {};
        itemInfo.itemTag = non;
        return itemInfo;
    }
}
