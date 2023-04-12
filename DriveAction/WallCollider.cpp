#include "WallCollider.h"

WallCollider::WallCollider(Actor* owner,VECTOR setFirstPos, VECTOR setEndPos)
    :ConflictProccesor(owner)
{
    firstPos = setFirstPos;
    endPos = setEndPos;
}

WallCollider::~WallCollider()
{
}

ConflictExamineResultInfo WallCollider::HitCheck(HitCheckExamineObjectInfo hitCheckInfo)
{
    ConflictExamineResultInfo resultInfo;
    resultInfo.SetObjInfo(object);
    resultInfo.hit = HitSituation::NotHit;

    if (hitCheckInfo.pos.x < firstPos.x || hitCheckInfo.pos.x > endPos.x
        || hitCheckInfo.pos.z < firstPos.z || hitCheckInfo.pos.z > endPos.z)
    {
        resultInfo.hit = HitSituation::Enter;
        resultInfo.pos = VSub(hitCheckInfo.pos, hitCheckInfo.velocity);
        resultInfo.bounceVec = VScale(VNorm(VSub(resultInfo.pos, hitCheckInfo.pos)),object->GetBouncePower());
    }
    return resultInfo;
}
