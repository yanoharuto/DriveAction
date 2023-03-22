#pragma once
#include <list>
#include "ConflictProccesor.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
/// <summary>
/// �����蔻���Z�߂Ă��邽�߂̓z
/// </summary>
class ConflictManager
{
public:
    ConflictManager();
    ~ConflictManager();
    /// <summary>
 /// �Ԃ����Ă邩���ׂ������ǉ�����
 /// </summary>
 /// <param name="obj"></param>
    static void AddConflictObjInfo(ConflictProccesor* conflictProccesor);
    static void EraceConflictObjInfo(ConflictProccesor* conflictProccesor);
    void DrawCollisionSphere();
    /// <summary>
    /// �����̃I�u�W�F�N�g�ƂԂ����Ă��邩���ׂ�
    /// </summary>
    /// <param name="examineObjInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo GetConflictObjInfo(ConflictProccesor* conflictProccesor);

    void Update();
private:
    static std::list<ConflictProccesor*> conflictObjList;
};