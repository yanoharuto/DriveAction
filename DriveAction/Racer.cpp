#include "Racer.h"
#include "Car.h"
#include "CheckPoint.h"
#include "HitChecker.h"
#include"Utility.h"
#include "OriginalMath.h"
static const float courceOutMaxCount = 5.8f;
Racer::Racer()
{
    checkPoint = new CheckPoint();
    itemHolder = new ItemHolder();
    rank = 0;
}

Racer::~Racer()
{
    SAFE_DELETE(checkPoint);
    SAFE_DELETE(itemHolder);
    SAFE_DELETE(car);
}

void Racer::Update(float deltaTime, bool outsideHitFlag,DamageObjectGenerator* damageObjGene)
{
    //プレイヤーと共通の処理
    CommonUpdate(deltaTime,outsideHitFlag,damageObjGene);
    ItemInfo itemInfo = itemHolder->GetItemInfo();
    //アイテムが使えるときは使う
    if (itemInfo.itemSituation != ItemUseSituation::DoneUsing && itemInfo.itemTag != non)
    {
        itemHolder->UseItem(car->GetItemArgumentInfo());
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
    itemHolder->ItemDraw();
}

void Racer::ConflictProcces(ConflictExamineResultInfo conflictResultInfo, float deltaTime)
{
    if (conflictResultInfo.tag == ObjectTag::itemBox)
    {
        itemHolder->SelectItem(rank);
    }
    else
    {
        car->ConflictProccess(deltaTime, conflictResultInfo);
    }
}

void Racer::CommonUpdate(float deltaTime, bool outsideHitFlag, DamageObjectGenerator* damageObjGene)
{
    //アイテムの更新
    itemHolder->Update(damageObjGene, car->GetItemArgumentInfo(), deltaTime);
    //車の当たり判定情報
    HitCheckExamineObjectInfo racerHitCheckExamineInfo;
    racerHitCheckExamineInfo.SetExamineInfo(*car);
    //車がチェックポイントを通過したか調べる
    ConflictExamineResultInfo conflictResultInfo = checkPoint->CheckPointUpdate(racerHitCheckExamineInfo);
    if (conflictResultInfo.hitFlag)
    {
        //車に次の目的地を伝える
        car->ConflictProccess(deltaTime, conflictResultInfo);
    }
    //コース外に出たら
    if (outsideHitFlag)
    {
        //コース外に出た時間を追加
        //courceOutCount += deltaTime;
        if (courceOutCount > courceOutMaxCount)
        {
            car->SetCourceOutProccess(checkPoint->GetLastPos(),checkPoint->GetLastDir());
            courceOutCount = 0.0f;
        }
    }
    else if (VDot(car->GetDir(), checkPoint->GetDir()) <= -0.5f)
    {
        //コース外に出た時間を追加
        //courceOutCount += deltaTime;
        if (courceOutCount > courceOutMaxCount)
        {
            car->SetCourceOutProccess(checkPoint->GetLastPos(), checkPoint->GetLastDir());
            courceOutCount = 0.0f;
        }
        reverse = true;
    }
    else
    {
        reverse = false;
        //コースから出ていなかったらコースアウト時間を減らす
        courceOutCount = courceOutCount > 0.001f ? courceOutCount - deltaTime : 0.0f;
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
