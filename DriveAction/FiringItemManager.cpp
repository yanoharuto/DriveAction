#include "FiringItemManager.h"
#include "Rocket.h"
#include "Utility.h"
FiringItemManager::FiringItemManager()
{
}

FiringItemManager::FiringItemManager(ConflictProcesser* processer)
{
    const char* string = rocketModelAddress.c_str();
    rocketModelHandle = MV1LoadModel(string);
    conflictProcesser = processer;
}

FiringItemManager::~FiringItemManager()
{
    for (int i = 0; i < damageObjList.size(); i++)
    {
        SAFE_DELETE(*damageObjList.end());
    }
}

void FiringItemManager::GenerateDamageObject(ItemTag itemTag, ItemArgumentCarInfo carInfo)
{
    DamageObject* obj;
    switch (itemTag)
    {
    case kite:
        obj = new Rocket(carInfo,rocketModelHandle);
        damageObjList.push_back(obj);
        conflictProcesser->AddConflictObject(obj);
        break;
    case accelerator:
        break;
    default:
        break;
    }
}

void FiringItemManager::ConflictUpdate(CircuitTrack* circuitTrack)
{
    for (auto objIte = damageObjList.begin(); objIte != damageObjList.end(); objIte++)
    {
        HitCheckExamineObjectInfo hitCheckExamineInfo;
        auto& obj = *(*objIte);
        hitCheckExamineInfo.SetExamineInfo(obj);
        auto courceResultInfo = circuitTrack->GetCourceConflictInfo(hitCheckExamineInfo);
        if (courceResultInfo.hitFlag || circuitTrack->GetOutsideHitFlag(hitCheckExamineInfo))
        {
            obj.ConflictProccess();
        }
    }
}

void FiringItemManager::Update(float deltaTime)
{
    for (auto objIte = damageObjList.begin(); objIte != damageObjList.end(); objIte++)
    {
        (*objIte)->Update(deltaTime);
       
    }
    auto objIte = damageObjList.begin();
    while (objIte != damageObjList.end()) 
    {
        if (!(*objIte)->GetAliveFlag()) 
        {
            objIte = damageObjList.erase(objIte);
        }
        else
        {
            ++objIte;
        }
    }
}

void FiringItemManager::Draw()
{
    for (auto objIte = damageObjList.begin(); objIte != damageObjList.end(); objIte++)
    {
        (*objIte)->Draw();
    }
}