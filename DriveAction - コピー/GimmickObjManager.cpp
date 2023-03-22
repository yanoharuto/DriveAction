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
    //������
    std::list<VECTOR> posList = courceDataLoader->GetAccelFloorPosList();
    std::list<VECTOR> dirList = courceDataLoader->GetAccelFloorDirList();
    auto dirIte = dirList.begin();
    for (auto posIte = posList.begin(); posIte != posList.end();posIte++)
    {
        //�|�W�V�����ƌ�����n��
        AccelerationFloor* floor = new AccelerationFloor(*posIte, *dirIte++);
        conflictProcesser->AddConflictObject(floor);//�Z�߂ē����蔻�������Ă����N���X�ɓn��
        actorList.push_back(floor);
    }
    //�A�C�e���{�b�N�X
    posList = courceDataLoader->GetItemPosList();
    dirList = courceDataLoader->GetItemDirList();
    dirIte = dirList.begin();
    itemBoxModelResource = MV1LoadModel(itemBoxModelAddress.c_str());
    for (auto posIte = posList.begin(); posIte != posList.end(); posIte++)
    {
        VECTOR pos = *posIte;
        VECTOR dir = *dirIte;
        pos = VAdd(pos, VScale(VCross(dir, VGet(0, 1, 0)), itemBoxNum / 2 * itemBoxBetween));
        for (int i = 0; i < itemBoxNum; i++)
        {
            ItemBox* itemBox;
            VECTOR addPos;
            pos = VAdd(pos, VScale(VCross(VGet(0, 1, 0), dir), itemBoxBetween));
            itemBox = new ItemBox(itemBoxModelResource, pos, dir);
            conflictProcesser->AddConflictObject(itemBox);
            actorList.push_back(itemBox);
        }
        dirIte++;
    }
    //�ۋ�
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

void GimmickObjManager::Update(float deltaTime)
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