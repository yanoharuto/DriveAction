#pragma once
#include <string>
#include <list>
#include "CheckPoint.h"
#include "FlyShipKind.h"
#include "PlayerRelatedInfo.h"
#include "LaserFlyShip.h"
#include "FlyShip.h"
class FlyShipInitializer
{
public:
    FlyShipInitializer();
    ~FlyShipInitializer();
    void IntFlyShip(FlyShipKind shipKind, PlayerRelatedInfo playerInfo, FlyShip* flyship);
private:
    //爆撃機のアドレス
    const std::string bomberModelPass = "Player/PrototypeZero.mv1";
    //modelのアドレス
    const std::string ufoModelPass = "Player/Rocker.mv1";
    const std::string ufoPosPass = "UFOPos.txt";
    std::list<VECTOR> ufoPosList;
};