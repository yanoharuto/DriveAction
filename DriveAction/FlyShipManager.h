#pragma once
#include <list>
#include "FlyShip.h"
#include "PlayerInformationCenter.h"
#include "Timer.h"
#include "BomberFlyShip.h"
#include "CircleLaserFlyShip.h"
#include "UpDownLaserFlyShip.h"
class FlyShipManager
{
public:
    FlyShipManager();
    ~FlyShipManager();
    void Update(PlayerInformationCenter* infoCenter);
    void Draw();
    void BomberInit(PlayerInformationCenter* infoCenter);
    void LaserInit(PlayerInformationCenter* infoCenter);
private:
    std::list<BomberFlyShip*>bombList;
    std::list<CircleLaserFlyShip*>UfoFlyshipList;
    std::list<UpDownLaserFlyShip*>updownFlyShipList;
    Timer* timer;
    const float setCoolTime = 5.0f;
    const int UFONum = 6;
    const int BomberFlyShipNum = 3;
    const float initBomberShipGeneratePosScale = 1000.0f;
    const float initBomberShipBetween = 300.0f;
    const float randomDegree = 60.0f;
    //
    int nowUFOPosIte = 0;
    //�����@�̃A�h���X
    const std::string bomberModelPass = "Player/PrototypeZero.mv1";
    //model�̃A�h���X
    const std::string ufoModelPass = "Player/Rocker.mv1";
    //���[�U�[�����Ă���G�̍��W
    const std::string ufoPosPass = "/UFOPos.txt";
    //���[�U�[�����Ă���G�Q�̍��W�������Ă���
    const std::string updownFlyShipPosPass = "/enemyPos.txt";
    
    std::list<VECTOR> ufoPosList;
    std::list<VECTOR> updownFlyShipPosList;
};