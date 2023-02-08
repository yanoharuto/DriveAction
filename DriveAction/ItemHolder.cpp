#include "ItemHolder.h"
#include "Kite.h"
#include "Accelerator.h"
#include "Utility.h"
ItemHolder::ItemHolder()
{
    item = nullptr;
}

ItemHolder::~ItemHolder()
{
    SAFE_DELETE(item);
}

void ItemHolder::Update(FiringItemManager* firingItemManager,ItemArgumentCarInfo carInfo,float deltaTime)
{
    if (item != nullptr)
    {
        ItemInfo itemInfo = item->GetItemInfo();
        switch (itemInfo.itemSituation)
        {
        case ItemUseSituation::nonUse:
            break;
        case ItemUseSituation::Useing:
            if (itemInfo.isFiriable)
            {
                firingItemManager->GenerateDamageObject(itemInfo.itemTag, carInfo);
            }
            item->Update(deltaTime);
            break;
        case ItemUseSituation::DoneUsing:
            SAFE_DELETE(item);
            break;
        default:
            break;
        }
        
    }
}

void ItemHolder::SelectItem(int rank)
{
    if (item == nullptr)
    {
        if (rank == 1)
        {
            item = new Accelerator();
        }
        else
        {
            item = new Kite();
        }
    }
}

void ItemHolder::ShowItem()
{
    item->ShowEffect();
}

ItemInfo ItemHolder::GetItemInfo()
{
    if (item != nullptr)
    {
        return item->GetItemInfo();
    }
    else
    {
        ItemInfo itemInfo = {};
        itemInfo.itemTag = non;
        return itemInfo;
    }
}
