#include "ConflictProcesser.h"
#include "HitChecker.h"
ConflictProcesser::ConflictProcesser()
{
}

ConflictProcesser::~ConflictProcesser()
{
}
/// <summary>
/// �Ԃ����Ă邩���ׂ������ǉ�����
/// </summary>
/// <param name="obj"></param>
void ConflictProcesser::AddConflictObject(Actor* obj)
{
    conflictObjList.push_back(obj);
}
/// <summary>
/// �����̃I�u�W�F�N�g�ƂԂ����Ă��邩���ׂ�
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