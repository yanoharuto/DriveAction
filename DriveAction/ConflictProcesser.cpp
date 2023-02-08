#include "ConflictProcesser.h"
#include "HitChecker.h"
ConflictProcesser::ConflictProcesser()
{
}

ConflictProcesser::~ConflictProcesser()
{
}

void ConflictProcesser::AddConflictObject(Actor* obj)
{
    conflictObjList.push_back(obj);
}

ConflictExamineResultInfo ConflictProcesser::GetConflictObjInfo(HitCheckExamineObjectInfo examineObjInfo)
{

    ConflictExamineResultInfo examineResultInfo = {};
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        if (*objIte != nullptr)
        {
            if((*objIte)->GetAliveFlag() && (*objIte)->HitCheckConflict(examineObjInfo))
            {
                examineResultInfo.SetObjInfo(true, (*objIte));
                (*objIte)->ConflictProccess();
            }
        }
    }
    return examineResultInfo;
}