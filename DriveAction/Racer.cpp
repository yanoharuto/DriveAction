#include "Racer.h"
#include "Car.h"
#include "CheckPoint.h"
#include "HitChecker.h"
#include"Utility.h"
Racer::Racer()
{
}

Racer::Racer(CircuitData circuitData)
{
    checkPoint = new CheckPoint(circuitData);
    soundPlayer = new SoundPlayer();
    itemHolder = new ItemHolder();
    rank = 0;
}

Racer::~Racer()
{
    SAFE_DELETE(checkPoint);
    SAFE_DELETE(soundPlayer);
    SAFE_DELETE(itemHolder);
    SAFE_DELETE(car);
}

void Racer::Update(float deltaTime, bool outsideHitFlag, FiringItemManager* firingItemManager)
{
    ItemInfo itemInfo = itemHolder->GetItemInfo();
    car->Update(deltaTime, outsideHitFlag,itemInfo, soundPlayer);

    if (itemInfo.itemSituation != ItemUseSituation::DoneUsing && itemInfo.itemTag != non)
    {
        itemHolder->ShowItem();
    }
    itemHolder->Update(firingItemManager, car->GetItemArgumentInfo(), deltaTime);
    HitCheckExamineObjectInfo racerHitCheckExamineInfo;
    racerHitCheckExamineInfo.SetExamineInfo(*car);
    //車がチェックポイントを通過したか調べる
    ConflictExamineResultInfo conflictResultInfo;
    conflictResultInfo = checkPoint->CheckPointUpdate(racerHitCheckExamineInfo);
    if (conflictResultInfo.hitFlag)
    {
        //車に次の目的地を伝える
        car->ConflictProcess(deltaTime, conflictResultInfo,soundPlayer);
    }
}

bool Racer::HitCheck(HitCheckExamineObjectInfo objInfo)
{
    HitChecker hitChecker;
    //当たってるか調べる　
    if (hitChecker.HitCheck(car, objInfo))
    {
        return true;
    }
    return false;
}

void Racer::Draw()
{
    car->Draw();
}

void Racer::ConflictProcces(ConflictExamineResultInfo conflictResultInfo, float deltaTime)
{
    if (conflictResultInfo.tag == ObjectTag::itemBox)
    {
        itemHolder->SelectItem(rank);
    }
    else
    {
        car->ConflictProcess(deltaTime, conflictResultInfo,soundPlayer);
    }
}

void Racer::SetCarPointer(Car* newCar)
{
    car = newCar;
}

HitCheckExamineObjectInfo Racer::GetCarHitCheckExamineInfo()
{
    HitCheckExamineObjectInfo objInfo;
    objInfo.SetExamineInfo(*car);
    return objInfo;
}

ConflictExamineResultInfo Racer::GetConflictExamineResultInfo()
{
    ConflictExamineResultInfo info;
    info.SetObjInfo(false,car);
    return info;
}

int* Racer::GetRankPointer()
{
    return &rank;
}

CheckPoint* Racer::GetCheckPointer()
{
    return checkPoint;
}
