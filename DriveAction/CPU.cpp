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
    car = new CPUCar(firstPos, VGet(1.0f,0,0));
    itemCoolTime = setItemCoolTime;

}

CPU::~CPU()
{
}

void CPU::Update()
{
    itemCoolTime -= DELTATIME;

    ItemArgumentCarInfo itemArgumentCarInfo;
    itemArgumentCarInfo.SetCarInfo(car);
    
    //�Ԃ̍X�V
    if (checkPoint->IsTransitCheckPoint(transitCPCount, car->GetHitCheckExamineInfo()))
    {
        transitCPCount++;
    }
    //���̃`�F�b�N�|�C���g�̍X�V
    HitCheckExamineObjectInfo carInfo;
    carInfo.SetExamineInfo(car);
}