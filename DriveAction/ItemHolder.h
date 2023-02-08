#pragma once
#include "Item.h"
#include "ConflictProcesser.h"
#include "FiringItemManager.h"
class ItemHolder
{
public:
    ItemHolder();
    ~ItemHolder();
    void Update(FiringItemManager* firingItemManager,ItemArgumentCarInfo carInfo,float deltaTime);
    void SelectItem(int rank);
    void ShowItem();
    ItemInfo GetItemInfo();
private:
    Item* item;
};