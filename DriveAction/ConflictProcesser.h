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