#pragma once
#include <list>
#include "DxLib.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "HitChecker.h"
#include "Object.h"
class ConflictProcesser
{
public:
    ConflictProcesser();
    ~ConflictProcesser();
    void AddConflictObject(Object* obj);
    ConflictExamineResultInfo GetConflictObjInfo(HitCheckExamineObjectInfo examineObjInfo);
private:
    std::list<Object*> conflictObjList;
};