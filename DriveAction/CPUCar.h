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
    CPUCar(VECTOR firstPos,VECTOR firstDir);
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
    void Init();
    const float turnProccesLine = 0.3f;//目的地に向かうときに曲がるか判断する
};

