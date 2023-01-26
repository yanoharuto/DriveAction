#include "GimmickObjManager.h"
#include "AccelerationFloor.h"
#include "Saw.h"
#include "Utility.h"
#include "HitChecker.h"
GimmickObjManager::GimmickObjManager()
{
}

GimmickObjManager::GimmickObjManager(ConflictProcesser* conflictProcesser,CourceDataLoader* courceDataLoader)
{
    std::list<VECTOR> posList = courceDataLoader->GetAccelFloorPosList();
    std::list<VECTOR> dirList = courceDataLoader->GetAccelFloorDirList();
    std::list<VECTOR>::iterator dirIte = dirList.begin();
    for (std::list<VECTOR>::iterator posIte = posList.begin(); posIte != posList.end();posIte++)
    {
        AccelerationFloor* floor = new AccelerationFloor(*posIte, *dirIte++);
        conflictProcesser->AddConflictObject(floor);
        accelerationFloorList.push_back(floor);
    }
    std::string address = courceDataLoader->GetObstracleAddress();
    modelResource = MV1LoadModel(address.c_str());
    posList = courceDataLoader->GetObstraclePosList();
    for (std::list<VECTOR>::iterator posIte = posList.begin(); posIte != posList.end(); posIte++)
    {

        Saw* obstracle = new Saw(*posIte,modelResource);
        conflictProcesser->AddConflictObject(obstracle);
        sawList.push_back(obstracle);
    }

}

GimmickObjManager::~GimmickObjManager()
{
    for (int i = 0; i < accelerationFloorList.size(); i++)
    {
        SAFE_DELETE((*accelerationFloorList.end()));
    }
    for (int i = 0; i < sawList.size(); i++)
    {
        SAFE_DELETE((*sawList.end()));
    }
    MV1DeleteModel(modelResource);
}

void GimmickObjManager::Draw()
{
    for (std::list<Saw*>::iterator objIte = sawList.begin(); objIte != sawList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
    for (std::list<AccelerationFloor*>::iterator objIte = accelerationFloorList.begin(); objIte != accelerationFloorList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}