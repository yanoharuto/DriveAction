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
/// �X�V
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
        //�A�C�e���̏�������
        ItemInfo itemInfo = item->GetItemInfo();
        //�A�C�e���̎g�p��
        switch (itemInfo.itemSituation)
        {
        case ItemUseSituation::Useing:
            //�A�C�e���̌��ʂ��X�V
            item->Update(deltaTime,carInfo);
            break;
        case ItemUseSituation::DoneUsing://�A�C�e�����g���I�������
            SAFE_DELETE(item);
            break;
        default:
            break;
        }
        
    }
}
/// <summary>
/// �A�C�e��������
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
/// �A�C�e�����g�p
/// </summary>
void ItemHolder::UseItem(ItemArgumentCarInfo carInfo)
{
    if (item != nullptr && !roulette)
    {
        item->ShowEffect(carInfo);
    }
}
/// <summary>
/// �A�C�e���̕`��
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
/// �A�C�e���̏���n��
/// </summary>
/// <returns>�����A�C�e���������ĂȂ��Ȃ�Tag��non</returns>
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
        //�����A�C�e���������ĂȂ��Ȃ�Tag��non
        ItemInfo itemInfo = {};
        itemInfo.itemTag = non;
        return itemInfo;
    }
}
