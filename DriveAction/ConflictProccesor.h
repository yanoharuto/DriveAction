#pragma once
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "Actor.h"
class  ConflictProccesor abstract
{
public:
    ConflictProccesor() {};
    ConflictProccesor(Actor* obj);
    virtual ~ConflictProccesor();
    virtual ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo) = 0;
    virtual HitCheckExamineObjectInfo GetHitExamineCheckInfo();
    virtual void ConflictProccess(ConflictExamineResultInfo resultInfo);
protected:
    Actor* object = nullptr;
};