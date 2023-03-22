#pragma once
#include "CourceDataLoader.h"
#include "Actor.h"
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
    void Update(float deltaTime);
    void Draw();
private:

    std::list<Actor*> actorList;
    int itemBoxNum = 6;
    const int itemBoxBetween = 25;
    //丸鋸のモデル
    int sawModelResource;
    //アイテムボックスのモデル
    int itemBoxModelResource;
    //丸鋸のmodelのアドレス
    const std::string obstacleModelAddress = "data/model/Saw/Saw.mv1";
    //アイテムボックスのアドレス
    const std::string itemBoxModelAddress = "data/model/Item/ItemBox/Box.mv1";
};

