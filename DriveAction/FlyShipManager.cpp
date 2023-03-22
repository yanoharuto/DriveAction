#include "FlyShipManager.h"
#include "LaserFlyShip.h"
#include "BomberFlyShip.h"
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
    for (int i = 0; i < UFONum * ufoPosList.size(); i++)
    {
        LaserFlyShip* flyship = new LaserFlyShip();
        UfoFlyshipList.push_back(flyship);
    }
    VECTOR generatePos = {};
    
    int j = 0;
    for (auto itr = ufoPosList.begin(); itr != ufoPosList.end(); itr++)
    {
        VECTOR dir = VGet(1, 0, 0);
        for (int i = 0; i < UFONum; i++)
        {
            dir = VNorm(OriginalMath::GetYRotateVector(dir, 60.0f));
            generatePos = VAdd((*itr), VScale(dir, 200.0f));
            auto obj = GetIncrementVector(UfoFlyshipList, i + j);
            obj ->Init(generatePos, (*itr));
        }
        j += UFONum;
    }

}

FlyShipManager::~FlyShipManager()
{
    for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
}

void FlyShipManager::Update(float deltaTime, PlayerInformationCenter* infoCenter)
{
    timer->Update(deltaTime);
    for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
    {
        if ((*ite)->GetAliveFlag())
        {
            (*ite)->Update(deltaTime);
        }
    }
    for (auto ite = UfoFlyshipList.begin(); ite != UfoFlyshipList.end(); ite++)
    {
        (*ite)->Update(deltaTime);
    }
    Init(infoCenter);
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
}

void FlyShipManager::Init(PlayerInformationCenter* infoCenter)
{
    if (timer->IsOverLimitTime())
    {
        PlayerRelatedInfo playerInfo = infoCenter->GetPlayerRelatedInfo(0);
        //出現場所
        VECTOR generatePos = {};
        //目標地点
        VECTOR destinationPos = {};
        VECTOR dir = {};

        while (VSize(dir) < 0.1f)
        {
            dir = VScale(VGet(OriginalMath::GetRandom(-1.0f, 1.0f), 0, OriginalMath::GetRandom(-1.0f, 1.0f)), 300.0f);
        }

        destinationPos = playerInfo.objInfo.pos;
        generatePos = VAdd(destinationPos, dir);
        dir = VScale(VCross(VNorm(VSub(destinationPos, generatePos)), VGet(0, 1, 0)), 100.0f);
        for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
        {
            (*ite)->Init(generatePos, destinationPos);
            generatePos = VAdd(generatePos, dir);
            destinationPos = VAdd(destinationPos, dir);
        }
    }
    if (timer->IsOverLimitTime())        timer->Init();
}