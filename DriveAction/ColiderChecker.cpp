#include "ColiderChecker.h"
#include "Actor.h"
#include "Stage.h"

#include "DxLib.h"
ColiderChecker::ColiderChecker()
{
}

ColiderChecker::~ColiderChecker()
{
}

void ColiderChecker::Check(Actor* const objA, Stage* const objB)
{
    VECTOR distance = VSub(objA->GetPos(), objB->GetPos());
    distance.y = 0;
    float range = objA->GetRadius() + objB->GetRadius();
    if (range > VSize(distance))
    {
        objB->ConflictProcess(objA);
    }
}