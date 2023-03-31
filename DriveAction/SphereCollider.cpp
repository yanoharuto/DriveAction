#include "SphereCollider.h"
#include "HitChecker.h"
#include "ConflictManager.h"
SphereCollider::SphereCollider(Actor* obj)
    :ConflictProccesor(obj)
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
        resultInfo.hit = HitSituation::Enter;
    }
    return resultInfo;
}
