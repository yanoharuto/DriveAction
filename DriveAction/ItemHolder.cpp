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
    if (item != nullptr)
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
    if (item == nullptr)
    {
        if (rank == 1)
        {
            item = new DamageImpactLauncher();
        }
        else
        {
            item = new Kite();
        }
    }
}
/// <summary>
/// アイテムを使用
/// </summary>
void ItemHolder::UseItem(ItemArgumentCarInfo carInfo)
{
    if (item != nullptr)
    {
        item->ShowEffect(carInfo);
    }
}
/// <summary>
/// アイテムの描画
/// </summary>
void ItemHolder::ItemDraw()
{
    if (item != nullptr)
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
    if (item != nullptr)
    {
        return item->GetItemInfo();
    }
    else
    {
        //何もアイテムを持ってないならTagはnon
        ItemInfo itemInfo = {};
        itemInfo.itemTag = non;
        return itemInfo;
    }
}
