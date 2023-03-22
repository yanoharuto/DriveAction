#include "ConflictProcesser.h"
#include "HitChecker.h"
ConflictProcesser::ConflictProcesser()
{
}

ConflictProcesser::~ConflictProcesser()
{
}
/// <summary>
/// ぶつかってるか調べたいやつを追加する
/// </summary>
/// <param name="obj"></param>
void ConflictProcesser::AddConflictObject(Actor* obj)
{
    conflictObjList.push_back(obj);
}
/// <summary>
/// 引数のオブジェクトとぶつかっているか調べる
/// </summary>
/// <param name="examineObjInfo"></param>
/// <returns></returns>
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