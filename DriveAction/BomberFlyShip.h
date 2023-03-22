#pragma once
#include "FlyShip.h"

class BomberFlyShip :
    public FlyShip
{
public:
    BomberFlyShip();
    BomberFlyShip(VECTOR setFirstPos, VECTOR setDestinationPos);
    ~BomberFlyShip();
    void Update(const float deltaTime) override;
private:
    //初期Y座標
    static const float setFirstPosY;
    //速さ
    static const float speed;
    //modelの大きさ
    static const float modelSize;
    //幅
    static const float setRadius;
    //爆弾の撃った回数
    int bomberCount = 0;
    //生存時間　爆弾発射クールタイム　最大高度　上昇速度
    static const FlyShipArgumentInfo setFlyShipParam;
};

