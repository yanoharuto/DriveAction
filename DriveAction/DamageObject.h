#pragma once
#include "Actor.h"
#include "ItemArgumentCarInfo.h"
#include "InitObjKind.h"
#include "ObjectObserver.h"

class DamageObject abstract:
    public Actor
{
public:
    DamageObject(Init::InitObjKind kind,ObjectObserver* setObserver);

    virtual ~DamageObject();
protected:
    ObjectObserver* observer;
};

