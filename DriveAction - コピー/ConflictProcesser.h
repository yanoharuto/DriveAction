#pragma once
#include <list>
#include "DxLib.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "HitChecker.h"
#include "Actor.h"
/// <summary>
/// 当たり判定を纏めてするための奴
/// </summary>
class ConflictProcesser
{
public:
    ConflictProcesser();
    ~ConflictProcesser();
    /// <summary>
    /// ぶつかってるか調べたいやつを追加する
    /// </summary>
    /// <param name="obj"></param>
    void AddConflictObject(Actor* obj);
    /// <summary>
    /// 引数のオブジェクトとぶつかっているか調べる
    /// </summary>
    /// <param name="examineObjInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo GetConflictObjInfo(HitCheckExamineObjectInfo examineObjInfo);
private:
    std::list<Actor*> conflictObjList;
};