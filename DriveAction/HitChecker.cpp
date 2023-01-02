#include "HitChecker.h"
#include "Object.h"

#include "DxLib.h"
HitChecker::HitChecker()
{
}

HitChecker::~HitChecker()
{
}

bool HitChecker::HitCheck(Object* const objA, Object* const objB)
{
    VECTOR distance = VSub(objA->GetPos(), objB->GetPos());
    distance.y = 0;
    float range = objA->GetRadius() + objB->GetRadius();
    if (range > VSize(distance))
    {
        return true;
    }
    return false;
}