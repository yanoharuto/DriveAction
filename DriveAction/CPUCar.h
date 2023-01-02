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
    
private:
    /// <summary>
    /// コンピューター版加速処理
    /// </summary>
    /// <param name="dir">向かう方向</param>
    /// <param name="outsideHitFlag">コース外にぶつかったか</param>
    /// <returns></returns>
    VECTOR GetAccelVec(const float dir,const bool outsideHitFlag);
    VECTOR firstPos = { -300.0f,-0.0f,-83.0f };//レース開始位置
    VECTOR firstDir = { -0.9f,0,-0.02f };//初期向き
    const float turnProccesLine = 0.4f;//目的地に向かうときに曲がるか判断する
};

