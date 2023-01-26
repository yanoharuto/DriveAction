#include "ConflictProcesser.h"
#include "HitChecker.h"
ConflictProcesser::ConflictProcesser()
{
}

ConflictProcesser::~ConflictProcesser()
{
}

void ConflictProcesser::AddConflictObject(Object* obj)
{
    conflictObjList.push_back(obj);
}

ConflictExamineResultInfo ConflictProcesser::GetConflictObjInfo(HitCheckExamineObjectInfo examineObjInfo)
{
    HitChecker checker;
    ConflictExamineResultInfo examineResultInfo = {};
    for (std::list<Object*>::iterator objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        if (*objIte != nullptr)
        {
            if (checker.HitCheck((*objIte), examineObjInfo))
            {
                examineResultInfo.SetObjInfo(true, (*objIte));
            }
        }
    }
    return examineResultInfo;
}