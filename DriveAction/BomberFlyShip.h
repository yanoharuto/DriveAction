#pragma once
#include "FlyShip.h"
class BomberFlyShip :
    public FlyShip
{
public:
    BomberFlyShip();
    BomberFlyShip(VECTOR setFirstPos, VECTOR setDestinationPos);
    ~BomberFlyShip();
    void Update() override;
    void Init(VECTOR newPosition, VECTOR newDestinationPos)override;
private:
    float coolTime;
    static const int SEVolume;
    static const std::string flightSE;
    //初期Y座標
    static const float setFirstPosY;
    //速さ
    static const float speed;
    //modelの大きさ
    static const float modelSize;
    //幅
    static const float setRadius;
    //生存時間　爆弾発射クールタイム　最大高度　上昇速度
    static const FlyShipArgumentInfo setFlyShipParam;
};

