#include "CPU.h"
#include "Utility.h"

CPU::CPU()
{
}

CPU::CPU(VECTOR firstPos,int duplicateModel)
{
    cpuCar = new CPUCar(firstPos, checkPoint->GetPos(),duplicateModel);
    SetCarPointer(cpuCar);
}

CPU::~CPU()
{
}

void CPU::Update(float deltaTime, bool outsideHitFlag, DamageObjectGenerator* damageObj)
{
    //ŽÔ‚ÌXV
    ItemInfo itemInfo = itemHolder->GetItemInfo();
    car->Update(deltaTime, outsideHitFlag, itemInfo);
    CommonUpdate(deltaTime, outsideHitFlag, damageObj);
    if (itemInfo.itemSituation == ItemUseSituation::nonUse && itemInfo.itemTag != non)
    {
        itemHolder->UseItem(car->GetItemArgumentInfo());
    }
}
