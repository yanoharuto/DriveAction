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
    rank = 0;
}

Racer::~Racer()
{
    SAFE_DELETE(checkPoint);
    SAFE_DELETE(car);
}

void Racer::Update()
{


}


void Racer::Draw()
{
    car->Draw();
}

void Racer::UpDown()
{
    car->UpDown();
}



int* Racer::GetRankPointer()
{
    return &rank;
}

CheckPoint* Racer::GetCheckPointer()
{
    return checkPoint;
}
