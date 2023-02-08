#pragma once
#include "DxLib.h"
#include "ItemArgumentCarInfo.h"
#include "ItemTag.h"
#include "ItemUseSituation.h"
#include "Actor.h"
#include "ItemInfo.h"
class Item abstract:Actor
{
public:
    Item();
    ~Item();
    virtual void Update(float deltaTime) = 0;
    virtual void ShowEffect() = 0;
    ItemInfo GetItemInfo();
protected:
    float effecacyValue;
    float effecacyTime = 0;
    float coolTime = -1;
    ItemUseSituation useSituation;
    ItemTag itemTag;
};

