#pragma once
#include "CourceDataLoader.h"
#include "Saw.h"
#include "AccelerationFloor.h"
#include "ConflictExamineResultInfo.h"
/// <summary>
/// 加速床とか障害物のマネージャー
/// </summary>
class GimmickObjManager
{
public:
    GimmickObjManager();
    GimmickObjManager(CourceDataLoader* courceDataLoader);
    ~GimmickObjManager();
    void Draw();
    /// <summary>
    /// 引数のオブジェクトとぶつかったギミックの情報を返す
    /// </summary>
    /// <param name="argumentObjInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo GetArgumentAndConflictGimmickInfo(ConflictExamineResultInfo argumentObjInfo);
private:
    std::list<Saw*> sawList;
    std::list<AccelerationFloor*> accelerationFloorList;
    int modelResource;
};

