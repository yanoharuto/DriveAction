#include "SphereCollider.h"
#include "HitChecker.h"
#include "ConflictManager.h"
SphereCollider::SphereCollider(Actor* obj)
    :ConflictProccesor(obj)
{
}

SphereCollider::~SphereCollider()
{
}

ConflictExamineResultInfo SphereCollider::HitCheck(HitCheckExamineObjectInfo hitCheckInfo)
{
    ConflictExamineResultInfo resultInfo = {};
    if (HitChecker::HitCheck(object, hitCheckInfo))
    {
        resultInfo.bounceVec = VSub(hitCheckInfo.pos, object->GetPos());
        resultInfo.pos = VAdd(hitCheckInfo.pos, resultInfo.bounceVec);
        resultInfo.tag = object->GetTag();
        resultInfo.hitFlag = true;
    }
    return resultInfo;
}
