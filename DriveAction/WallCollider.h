#pragma once
#include "ConflictProccesor.h"
class WallCollider :
    public ConflictProccesor
{
public:
    WallCollider(Actor* owner,VECTOR setFirstPos,VECTOR setEndPos);
    ~WallCollider();
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo) override;
private:
    VECTOR firstPos;
    VECTOR endPos;
};

