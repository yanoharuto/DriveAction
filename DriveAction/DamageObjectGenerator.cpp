#include "DamageObjectGenerator.h"
#include "Rocket.h"
#include "DamageImpact.h"
#include "RotatingLasers.h"
#include "FiringItemManager.h"
DamageObjectGenerator::DamageObjectGenerator()
{    

}
DamageObjectGenerator::~DamageObjectGenerator()
{
}
/// <summary>
/// アイテムの種類によって生成するアイテムを変更する
/// </summary>
/// <param name="itemTag"></param>
/// <param name="carInfo"></param>
Actor* DamageObjectGenerator::GenerateDamageObject(ItemTag itemTag, ItemArgumentCarInfo carInfo,FiringObjOwner* owner)
{
    Actor* obj = nullptr;

    switch (itemTag)
    {
    case bomber:
        obj = new Rocket(carInfo);
        break;
    case ufo:
        obj = new RotatingLasers(owner);
        break;
    default:
        obj = new DamageImpact(carInfo);
        break;
    }
    FiringItemManager::AddFiringObject(obj);
    return obj;
}