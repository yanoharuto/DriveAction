#pragma once
#include "Actor.h"
#include "ItemArgumentCarInfo.h"
class DamageObject abstract:
    public Actor
{
public:
    DamageObject() {};
    DamageObject(ItemArgumentCarInfo carInfo);
    virtual ~DamageObject();
};

