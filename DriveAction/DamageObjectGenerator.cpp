#include "DamageObjectGenerator.h"
#include "Rocket.h"
#include "DamageImpact.h"
static ConflictProcesser* conflictProccer;
static FiringItemManager* firingItemManager;
DamageObjectGenerator::DamageObjectGenerator()
{    
    conflictProccer = nullptr;
    firingItemManager = nullptr;
}
DamageObjectGenerator::DamageObjectGenerator(ConflictProcesser* conflictPro, FiringItemManager* firingItemMana)
{
    conflictProccer = conflictPro;
    firingItemManager = firingItemMana;
}

DamageObjectGenerator::~DamageObjectGenerator()
{
}
/// <summary>
/// アイテムの種類によって生成するアイテムを変更する
/// </summary>
/// <param name="itemTag"></param>
/// <param name="carInfo"></param>
void DamageObjectGenerator::GenerateDamageObject(ItemTag itemTag, ItemArgumentCarInfo carInfo)
{
    DamageObject* obj = nullptr;

    switch (itemTag)
    {
    case kite:
        obj = new Rocket(carInfo);
        break;
    case accelerator:
        break;
    case attack:
        obj = new DamageImpact(carInfo);
        break;
    default:
        break;
    }
    
    firingItemManager->AddDamageObject(obj);
    conflictProccer->AddConflictObject(obj);
}