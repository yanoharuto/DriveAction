#pragma once
#include "FiringObjOwner.h"
#include "RotatingLasers.h"
class BigRadiusLaser:public RotatingLasers
{
public:
    BigRadiusLaser(FiringObjOwner* setOwner);

    /// <summary>
/// 回転させる
/// </summary>
/// <param name="deltaTime"></param>
    void Update()override;

private:
    //レーザーエフェクトのパス
    static const InitParam initParam;
    
    //回転速度
    static const float rotaSpeed;
    FiringObjOwner* owner;
};

