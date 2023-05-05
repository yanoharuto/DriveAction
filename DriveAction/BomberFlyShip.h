#pragma once
#include "FlyShip.h"
#include <string>
struct FlyShipArgumentInfo;
class Timer;
/// <summary>
/// 爆撃機
/// </summary>
class BomberFlyShip :
    public FlyShip
{
public:
    /// <summary>
    /// 爆撃機
    /// </summary>
    /// <param name="setFirstPos">出現位置</param>
    /// <param name="setDestinationPos">目的地</param>
    BomberFlyShip(VECTOR setFirstPos, VECTOR setDestinationPos);
    /// <summary>
    /// 爆弾を落としながら進む
    /// </summary>
    void Update() override;
private:
    Timer* timer;
    static const int SEVolume;
    static const std::string flightSE;
    //速さ
    static const float speed;
    //生存時間　爆弾発射クールタイム　最大高度　上昇速度
    static const FlyShipArgumentInfo setFlyShipParam;
};

