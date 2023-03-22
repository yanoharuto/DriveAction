#include "ConflictManager.h"
std::list<ConflictProccesor*> ConflictManager::conflictObjList;
ConflictManager::ConflictManager()
{
}

ConflictManager::~ConflictManager()
{
}
void ConflictManager::AddConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    conflictObjList.push_back(conflictProccesor);
}



void ConflictManager::EraceConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    auto procceesor = std::find(conflictObjList.begin(), conflictObjList.end(), conflictProccesor);
    if (procceesor != conflictObjList.end())
    {
        conflictObjList.erase(procceesor);
    }
}

void ConflictManager::DrawCollisionSphere()
{
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
       HitCheckExamineObjectInfo info = (*objIte)->GetHitExamineCheckInfo();
        DrawSphere3D(info.pos, info.radius, 4, GetColor(200, 200, 200), GetColor(200, 200, 200), false);
    }
}

/// <summary>
/// 引数のオブジェクトとぶつかっているか調べる
/// </summary>
/// <param name="examineObjInfo"></param>
/// <returns></returns>
ConflictExamineResultInfo ConflictManager::GetConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    ConflictExamineResultInfo examineResultInfo = {};
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        if (conflictProccesor != (*objIte))
        {
            examineResultInfo = (*objIte)->HitCheck(conflictProccesor->GetHitExamineCheckInfo());
            if (examineResultInfo.hitFlag) 
            {
                return examineResultInfo;
            }
        }
    }
    examineResultInfo = {};
    return examineResultInfo;
}

void ConflictManager::Update()
{
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        ConflictExamineResultInfo resultInfo = GetConflictObjInfo((*objIte));
        if (resultInfo.hitFlag)
        {
            (*objIte)->ConflictProccess(resultInfo);
        }
    }
}
