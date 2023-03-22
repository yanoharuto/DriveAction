#include "conflictProccesor.h"
#include "HitChecker.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
ConflictProccesor::ConflictProccesor(Actor* obj)
{
    object = obj;
    ConflictManager::AddConflictObjInfo(this);
}

ConflictProccesor::~ConflictProccesor()
{

}

HitCheckExamineObjectInfo ConflictProccesor::GetHitExamineCheckInfo()
{
    HitCheckExamineObjectInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}

void ConflictProccesor::ConflictProccess(ConflictExamineResultInfo resultInfo)
{
    object->ConflictProccess(resultInfo);
}
