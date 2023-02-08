#pragma once
#include <list>
#include <string>
#include "DamageObject.h"
#include "CircuitTrack.h"
#include "ItemArgumentCarInfo.h"
#include "ItemTag.h"
#include "ConflictProcesser.h"
class FiringItemManager
{
public:
    FiringItemManager();
    FiringItemManager(ConflictProcesser* conflictProcesser);
    ~FiringItemManager();
    void GenerateDamageObject(ItemTag itemTag,ItemArgumentCarInfo carInfo);
    void ConflictUpdate(CircuitTrack* conflictProccess);
    void Update(float deltaTime);
    void Draw();
private:
    std::list<DamageObject*> damageObjList;
    std::string rocketModelAddress = "data/model/Rocket/Rocket04_Grey.mv1";
    int rocketModelHandle;
    ConflictProcesser* conflictProcesser;
};