#include "GimmickObjManager.h"
#include "AccelerationFloor.h"
#include "Saw.h"
#include "ItemBox.h"
#include "Utility.h"
GimmickObjManager::GimmickObjManager()
{
}

GimmickObjManager::GimmickObjManager(ConflictProcesser* conflictProcesser,CourceDataLoader* courceDataLoader)
{
    //加速床
    std::list<VECTOR> posList = courceDataLoader->GetAccelFloorPosList();
    std::list<VECTOR> dirList = courceDataLoader->GetAccelFloorDirList();
    auto dirIte = dirList.begin();
    for (auto posIte = posList.begin(); posIte != posList.end();posIte++)
    {
        //ポジションと向きを渡す
        AccelerationFloor* floor = new AccelerationFloor(*posIte, *dirIte++);
        conflictProcesser->AddConflictObject(floor);//纏めて当たり判定をやってくれるクラスに渡す
        actorList.push_back(floor);
    }
    //アイテムボックス
    posList = courceDataLoader->GetItemPosList();
    dirList = courceDataLoader->GetItemDirList();
    dirIte = dirList.begin();
    itemBoxModelResource = MV1LoadModel(itemBoxModelAddress.c_str());
    for (auto posIte = posList.begin(); posIte != posList.end(); posIte++)
    {
        VECTOR pos = *posIte;
        VECTOR dir = *dirIte;
        
        for (int i = 0; i < 4; i++)
        {
            ItemBox* itemBox;
            VECTOR addPos;
            if (i % 2 == 1)
            {
                addPos = VScale(VCross(dir, VGet(0, 1, 0)), i * 15);
            }
            else
            {
                addPos = VScale(VCross(dir, VGet(0, -1, 0)), i * 15);
            }
            itemBox = new ItemBox(itemBoxModelResource, VAdd(pos,addPos), dir);
            conflictProcesser->AddConflictObject(itemBox);
            actorList.push_back(itemBox);
        }
    }
    //丸鋸
    sawModelResource = MV1LoadModel(obstacleModelAddress.c_str());
    posList = courceDataLoader->GetObstraclePosList();
    for (auto posIte = posList.begin(); posIte != posList.end(); posIte++)
    {
        Saw* obstracle = new Saw(*posIte,sawModelResource);
        conflictProcesser->AddConflictObject(obstracle);
        actorList.push_back(obstracle);
    }

}

GimmickObjManager::~GimmickObjManager()
{
    for (int i = 0; i < actorList.size(); i++)
    {
        SAFE_DELETE((*actorList.end()));
    }

    MV1DeleteModel(sawModelResource);
    MV1DeleteModel(itemBoxModelResource);
}

void GimmickObjManager::Updatee(float deltaTime)
{
    for (auto objIte = actorList.begin(); objIte != actorList.end(); objIte++)
    {
        (*objIte)->Update(deltaTime);
    }
}

void GimmickObjManager::Draw()
{
    for (auto objIte = actorList.begin(); objIte != actorList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}