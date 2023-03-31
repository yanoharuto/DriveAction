#include "FlyShipManager.h"

#include "Utility.h"
#include "ListUtility.h"
#include "CourceDataLoader.h"

FlyShipManager::FlyShipManager()
{
    timer = new Timer(setCoolTime);
    for (int i = 0; i < BomberFlyShipNum; i++)
    {
        BomberFlyShip* flyship = new BomberFlyShip();
        bombList.push_back(flyship);
    }  

    ufoPosList = CourceDataLoader::GetVECTORData(ufoPosPass);
    VECTOR generatePos = {};
    int j = 0;
    for (auto itr = ufoPosList.begin(); itr != ufoPosList.end(); itr++)
    {
        VECTOR dir = VGet(1, 0, 0);
        for (int i = 0; i < UFONum; i++)
        {
            dir = VNorm(OriginalMath::GetYRotateVector(dir, 60.0f));
            generatePos = VAdd((*itr), VScale(dir, 200.0f));
            CircleLaserFlyShip* flyship = new CircleLaserFlyShip(generatePos, (*itr));
            UfoFlyshipList.push_back(flyship);
        }
        j += UFONum;
    }

    updownFlyShipPosList = CourceDataLoader::GetVECTORData(updownFlyShipPosPass);
    for (auto itr = updownFlyShipPosList.begin(); itr != updownFlyShipPosList.end(); itr++)
    {
        UpDownLaserFlyShip* flyship = new UpDownLaserFlyShip((*itr),VGet(0,0,0));
        updownFlyShipList.push_back(flyship);
    }
}

FlyShipManager::~FlyShipManager()
{
    for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
}

void FlyShipManager::Update( PlayerInformationCenter* infoCenter)
{
    timer->Update();
    for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
    {
        if ((*ite)->GetAliveFlag())
        {
            (*ite)->Update();
        }
    }
    for (auto ite = UfoFlyshipList.begin(); ite != UfoFlyshipList.end(); ite++)
    {
        (*ite)->Update();
    }
    for (auto ite = updownFlyShipList.begin(); ite != updownFlyShipList.end(); ite++)
    {
        (*ite)->Update();
    }
    BomberInit(infoCenter);
    LaserInit(infoCenter);
}

void FlyShipManager::Draw()
{
    for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
    {
        (*ite)->Draw();
    }
    for (auto ite = UfoFlyshipList.begin(); ite != UfoFlyshipList.end(); ite++)
    {
        (*ite)->Draw();
    }
    for(auto ite = updownFlyShipList.begin(); ite != updownFlyShipList.end(); ite++)
    {
        (*ite)->Draw();
    }
}

void FlyShipManager::BomberInit(PlayerInformationCenter* infoCenter)
{
    if (timer->IsOverLimitTime())
    {
        PlayerRelatedInfo playerInfo = infoCenter->GetPlayerRelatedInfo(0);
        //出現場所
        VECTOR generatePos = {};
        //目標地点
        VECTOR destinationPos = {};
        VECTOR dir = {};


        dir = VNorm(OriginalMath::GetYRotateVector(playerInfo.objInfo.dir, OriginalMath::GetRandom(-randomDegree,randomDegree)));
        destinationPos = playerInfo.objInfo.pos;
        generatePos = VAdd(destinationPos, VScale(dir,initBomberShipGeneratePosScale));
        dir = VScale(VCross(VNorm(VSub(destinationPos, generatePos)), VGet(0, 1, 0)), initBomberShipBetween);
        for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
        {
            (*ite)->Init(generatePos, destinationPos);
            generatePos = VAdd(generatePos, dir);
            destinationPos = VAdd(destinationPos, dir);
        }
    }
    if (timer->IsOverLimitTime())        timer->Init();
}

void FlyShipManager::LaserInit(PlayerInformationCenter* infoCenter)
{
    for (auto ite = UfoFlyshipList.begin(); ite != UfoFlyshipList.end(); ite++)
    {
        (*ite)->Init(infoCenter->GetPlayerRelatedInfo(0).objInfo.pos);
    }

    for (auto ite = updownFlyShipList.begin(); ite != updownFlyShipList.end(); ite++)
    {
        (*ite)->Init(infoCenter->GetPlayerRelatedInfo(0).objInfo.pos);
    }
}