#include "FiringItemManager.h"
#include "Rocket.h"
#include "Utility.h"
FiringItemManager::FiringItemManager()
{
}

FiringItemManager::~FiringItemManager()
{
    for (auto ite = damageObjList.begin(); ite != damageObjList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
}

void FiringItemManager::AddDamageObject(DamageObject* damageObj)
{
    damageObjList.push_back(damageObj);
}

void FiringItemManager::CircuitTrackConflictProccess(CircuitTrack* circuitTrack)
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