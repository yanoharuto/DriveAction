#include "FlyShipManager.h"
#include "ListUtility.h"
#include "GetGeneratePos.h"
#include "Utility.h"
#include "CourceDataLoader.h"
#include "Timer.h"
#include "BomberFlyShip.h"
#include "CircleLaserFlyShip.h"
#include "UpDownLaserFlyShip.h"
#include "OriginalMath.h"
#include "RacerManager.h"
#include "SubjectInfoCentor.h"
/// <summary>
/// ����ԑD�̃}�l�[�W���[
/// </summary>
/// <param name="racerManager"></param>
FlyShipManager::FlyShipManager(RacerManager* racerManager)
{
    bomberFlyShipGoTimer = new Timer(setBShipInitSpan);
    playerObserver = SubjectInfoCentor::GetObjectObserver(racerManager->GetPlayerSubject(0));
    LaserShipInit();
}

FlyShipManager::~FlyShipManager()
{
    for (auto ite = bombList.begin(); ite != bombList.end(); ite++)
    {
        SAFE_DELETE(*ite);
    }
}

void FlyShipManager::Update()
{
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
    BomberShipInit();
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
/// <summary>
/// �����@�̏������@
/// </summary>
/// <param name="infoCenter"></param>
void FlyShipManager::BomberShipInit()
{
    //���Ԃ��߂�����܂������@�𔭐i
    if (bomberFlyShipGoTimer->IsOverLimitTime())
    {
        //�����_���Ȋp�x���o��
        int randomNum = OriginalMath::GetRandom(0, bShipInitRandDeg);
        //�����_���ȕ������甚���@�𔭐i������
        VECTOR dir = OriginalMath::GetYRotateVector(VGet(1, 0, 0), static_cast<float> (randomNum));
        //�v���C���[�Ɍ�������
        VECTOR destinationPos = playerObserver->GetSubPos();
        //�o���ꏊ
        VECTOR generatePos = VAdd(destinationPos, VScale(dir,initBShipGeneratePosScale));
        //��@�ڈȍ~�͑��̋@�̂Ƌ�����u���Ĕ��i
        VECTOR between = VScale(VCross(VNorm(VSub(destinationPos, generatePos)), VGet(0, 1, 0)), initBShipBetween);
        //������
        for (int i = 0; i < BomberFlyShipNum; i++)
        {
            generatePos = VAdd(generatePos, between);
            destinationPos = VAdd(destinationPos, between);
            BomberFlyShip* flyship = new BomberFlyShip(generatePos,destinationPos);
            bombList.push_back(flyship);
        }
        //�܂����Ԃ������甭�i
        bomberFlyShipGoTimer->Init();
    }
}

void FlyShipManager::LaserShipInit()
{
    std::list<VECTOR> circleLaserShipPosList = ConvertVectorToList(GetGeneratePos::CSVConvertPosition(enemyPosPass, 0));
    VECTOR generatePos = {};
    int j = 0;
    for (auto itr = circleLaserShipPosList.begin(); itr != circleLaserShipPosList.end(); itr++)
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

    std::list<VECTOR>updownFlyShipPosList = ConvertVectorToList(GetGeneratePos::CSVConvertPosition(enemyPosPass, 1));
    for (auto itr = updownFlyShipPosList.begin(); itr != updownFlyShipPosList.end(); itr++)
    {
        UpDownLaserFlyShip* flyship = new UpDownLaserFlyShip((*itr), VGet(0, 0, 0));
        updownFlyShipList.push_back(flyship);
    }
}