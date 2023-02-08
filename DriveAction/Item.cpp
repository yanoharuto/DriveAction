#include "Item.h"


Item::Item()
{
    useSituation = ItemUseSituation::nonUse;
    effecacyValue = {};
    itemTag = non;
}

Item::~Item()
{
}

void Item::ShowEffect()
{
}

ItemInfo Item::GetItemInfo()
{
    return {effecacyValue,coolTime < -0.1f,itemTag,useSituation};
}
