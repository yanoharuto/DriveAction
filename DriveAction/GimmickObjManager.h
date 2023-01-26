#pragma once
#include "CourceDataLoader.h"
#include "Saw.h"
#include "AccelerationFloor.h"
#include "ConflictExamineResultInfo.h"
#include "ConflictProcesser.h"
/// <summary>
/// 加速床とか障害物のマネージャー
/// </summary>
class GimmickObjManager
{
public:
    GimmickObjManager();
    GimmickObjManager(ConflictProcesser* conflictProcesser ,CourceDataLoader* courceDataLoader);
    ~GimmickObjManager();
    void Draw();
private:
    std::list<Saw*> sawList;
    std::list<AccelerationFloor*> accelerationFloorList;
    int modelResource;
};

