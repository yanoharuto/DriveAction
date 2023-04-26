#include "FlyShipManager.h"
#include "ListUtility.h"
#include "GetGeneratePos.h"
#include "Utility.h"
#include "CourceDataLoader.h"

FlyShipManager::FlyShipManager()
{
    bomberFlyShipGoTimer = new Timer(setBShipInitSpan);
    for (int i = 0; i < BomberFlyShipNum; i++)
    {
        BomberFlyShip* flyship = new BomberFlyShip();
        bombList.push_back(flyship);
    }  

    std::list<VECTOR> ufoPosList = ConvertVectorToList(GetGeneratePos::CSVConvertPosition(enemyPosPass,0));
    VECTOR generatePos = {};
    int j = 0;
    for (auto itr = ufoPosList.begin(); itr != ufoPosList.end(); itr++)
    {
        VECTOR dir = VGet(1, 0, 0);
        for (int i = 0; i < circleShipNum; i++)
        {
            dir = VNorm(OriginalMath::GetYRotateVector(dir, 60.0f));
            generatePos = VAdd((*itr), VScale(dir, 200.0f));
            CircleLaserFlyShip* flyship = new CircleLaserFlyShip(generatePos, (*itr));
            circleFlyshipList.push_back(flyship);
        }
        j += circleShipNum;
    }

    std::list<VECTOR>updownFlyShipPosList = ConvertVectorToList(GetGeneratePos::CSVConvertPosition(enemyPosPass,1));
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
    bomberFlyShipGoTimer->Update();
    for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
    {
        if ((*ite)->GetAliveFlag())
        {
            (*ite)->Update();
        }
    }
    for (auto ite = circleFlyshipList.begin(); ite != circleFlyshipList.end(); ite++)
    {
        (*ite)->Update();
    }
    for (auto ite = updownFlyShipList.begin(); ite != updownFlyShipList.end(); ite++)
    {
        (*ite)->Update();
    }
    BomberShipInit(infoCenter);
    LaserShipInit(infoCenter);
}

void FlyShipManager::Draw()
{
    for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
    {
        (*ite)->Draw();
    }
    for (auto ite = circleFlyshipList.begin(); ite != circleFlyshipList.end(); ite++)
    {
        (*ite)->Draw();
    }
    for(auto ite = updownFlyShipList.begin(); ite != updownFlyShipList.end(); ite++)
    {
        (*ite)->Draw();
    }
}

void FlyShipManager::BomberShipInit(PlayerInformationCenter* infoCenter)
{
    //���Ԃ��߂�����܂������@�𔭐M
    if (bomberFlyShipGoTimer->IsOverLimitTime())
    {
        PlayerRelatedInfo playerInfo = infoCenter->GetPlayerRelatedInfo(0);
        //�����_���Ȋp�x���o��
        int randomNum = OriginalMath::GetRandom(0, bShipInitRandDeg);
        //�����_���ȕ������甚���@�𔭐i������
        VECTOR dir = OriginalMath::GetYRotateVector(VGet(1, 0, 0), static_cast<float> (randomNum));
        //�v���C���[�Ɍ�������
        VECTOR destinationPos = playerInfo.objInfo.pos;
        //�o���ꏊ
        VECTOR generatePos = VAdd(destinationPos, VScale(dir,initBShipGeneratePosScale));
        //��@�ڈȍ~�͑��̋@�̂Ƌ�����u���Ĕ��i
        VECTOR between = VScale(VCross(VNorm(VSub(destinationPos, generatePos)), VGet(0, 1, 0)), initBShipBetween);
        //������
        for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
        {
            (*ite)->Init(generatePos, destinationPos);
            generatePos = VAdd(generatePos, between);
            destinationPos = VAdd(destinationPos, between);
        }

        bomberFlyShipGoTimer->Init();
    }
}

void FlyShipManager::LaserShipInit(PlayerInformationCenter* infoCenter)
{
    for (auto ite = circleFlyshipList.begin(); ite != circleFlyshipList.end(); ite++)
    {
        (*ite)->Init(infoCenter->GetPlayerRelatedInfo(0));
    }

    for (auto ite = updownFlyShipList.begin(); ite != updownFlyShipList.end(); ite++)
    {
        (*ite)->Init(infoCenter->GetPlayerRelatedInfo(0));
    }
}