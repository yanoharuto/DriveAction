#include "CPU.h"
#include "Utility.h"
#include "DirectionOfTravelGenerator.h"
#include "Utility.h"
#include "FlyShipKind.h"
CPU::CPU()
{
}

CPU::CPU(VECTOR firstPos)
{
    cpuCar = new CPUCar(firstPos, VGet(1.0f,0,0));
    SetCarPointer(cpuCar);
    itemCoolTime = setItemCoolTime;

}

CPU::~CPU()
{
}

void CPU::Update(float deltaTime)
{
    itemCoolTime -= deltaTime;

    ItemInfo itemInfo = itemHolder->GetItemInfo();

    ItemArgumentCarInfo itemArgumentCarInfo;
    itemArgumentCarInfo.SetCarInfo(car);
    itemHolder->Update(itemArgumentCarInfo, deltaTime);
    //�Ԃ̍X�V
    car->Update(deltaTime, checkPoint->GetCheckPointPos(transitCPCount), itemInfo);
    if (checkPoint->IsTransitCheckPoint(transitCPCount, car->GetHitCheckExamineInfo()))
    {
        transitCPCount++;
    }
    //���̃`�F�b�N�|�C���g�̍X�V
    HitCheckExamineObjectInfo carInfo;
    carInfo.SetExamineInfo(car);
}