#pragma once
#include <list>
#include "DxLib.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "HitChecker.h"
#include "Actor.h"
class ConflictProcesser
{
public:
    ConflictProcesser();
    ~ConflictProcesser();
    /// <summary>
    /// �Ԃ����Ă邩���ׂ������ǉ�����
    /// </summary>
    /// <param name="obj"></param>
    void AddConflictObject(Actor* obj);
    /// <summary>
    /// �����̃I�u�W�F�N�g�ƂԂ����Ă��邩���ׂ�
    /// </summary>
    /// <param name="examineObjInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo GetConflictObjInfo(HitCheckExamineObjectInfo examineObjInfo);
private:
    std::list<Actor*> conflictObjList;
};