#include "Racer.h"
#include "Car.h"
#include "CheckPoint.h"
#include "HitChecker.h"
#include"Utility.h"
#include "OriginalMath.h"
#include "DirectionOfTravelGenerator.h"
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

void Racer::Update(float deltaTime)
{


}

bool Racer::HitCheck(HitCheckExamineObjectInfo objInfo)
{
    HitChecker hitChecker;
    //“–‚½‚Á‚Ä‚é‚©’²‚×‚é@
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

void Racer::SetCarPointer(Car* newCar)
{
    car = newCar;
}

HitCheckExamineObjectInfo Racer::GetCarHitCheckExamineInfo()
{
    return car->GetHitCheckExamineInfo();
}


int* Racer::GetRankPointer()
{
    return &rank;
}

CheckPoint* Racer::GetCheckPointer()
{
    return checkPoint;
}
