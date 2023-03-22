#pragma once
#include <list>
#include "FlyShip.h"
#include "PlayerInformationCenter.h"
#include "Timer.h"
#include "BomberFlyShip.h"
#include "LaserFlyShip.h"
class FlyShipManager
{
public:
    FlyShipManager();
    ~FlyShipManager();
    void Update(float deltaTime,PlayerInformationCenter* infoCenter);
    void Draw();
    void Init(PlayerInformationCenter* infoCenter);
private:
    std::list<BomberFlyShip*>bombList;
    std::list<LaserFlyShip*>UfoFlyshipList;
    Timer* timer;
    const float setCoolTime = 5.0f;
    const int UFONum = 6;
    const int BomberFlyShipNum = 3;
    int nowUFOPosIte = 0;
    //爆撃機のアドレス
    const std::string bomberModelPass = "Player/PrototypeZero.mv1";
    //modelのアドレス
    const std::string ufoModelPass = "Player/Rocker.mv1";
    const std::string ufoPosPass = "/UFOPos.txt";
    std::list<VECTOR> ufoPosList;
};