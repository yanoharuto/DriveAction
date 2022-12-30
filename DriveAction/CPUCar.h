#pragma once
#include "Car.h"
/// <summary>
/// 自動運転の車
/// </summary>
class CPUCar :
    public Car
{
public:
    CPUCar();
    ~CPUCar();
    void Update(const float deltaTime,const bool outsideHitFlag)override;
    void ConflictProcess(Object* object) override;
private:
    VECTOR GetAccelVec(const float dir,const bool outsideHitFlag);
    VECTOR destinationPos;
    VECTOR firstPos = { -300.0f,-0.0f,-83.0f };//レース開始位置
    VECTOR firstDir = { -0.9f,0,-0.02f };//初期向き
    const float calculationLine = 0.2f;
};

