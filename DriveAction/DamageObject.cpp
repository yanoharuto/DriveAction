#include "DamageObject.h"

DamageObject::DamageObject(Init::InitObjKind kind, ObjectObserver* setObserver)
    :Actor(kind)
{
    observer = setObserver;
}

DamageObject::~DamageObject()
{
}