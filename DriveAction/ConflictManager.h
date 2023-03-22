#pragma once
#include <list>
#include "ConflictProccesor.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
/// <summary>
/// 当たり判定を纏めてするための奴
/// </summary>
class ConflictManager
{
public:
    ConflictManager();
    ~ConflictManager();
    /// <summary>
 /// ぶつかってるか調べたいやつを追加する
 /// </summary>
 /// <param name="obj"></param>
    static void AddConflictObjInfo(ConflictProccesor* conflictProccesor);
    static void EraceConflictObjInfo(ConflictProccesor* conflictProccesor);
    void DrawCollisionSphere();
    /// <summary>
    /// 引数のオブジェクトとぶつかっているか調べる
    /// </summary>
    /// <param name="examineObjInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo GetConflictObjInfo(ConflictProccesor* conflictProccesor);

    void Update();
private:
    static std::list<ConflictProccesor*> conflictObjList;
};