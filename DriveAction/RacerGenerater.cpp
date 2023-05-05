#include "RacerGenerater.h"
#include "CPU.h"
#include "Player.h"
#include "CourceDataLoader.h"
#include "GetGeneratePos.h"
#include "ListUtility.h"
#include "RaceCamera.h"
#include "ShadowMap.h"
#include "PlayerRelatedUI.h"
#include "ObjectSubject.h"
#include "ObjectObserver.h"
#include "SubjectInfoCentor.h"
RacerGenerater::RacerGenerater()
{
}
Player* RacerGenerater::CreatePlayer(int racerNum)
{
    std::vector<VECTOR> firstPosList = GetGeneratePos::CSVConvertPosition(firstPosPass, 0);
    //ポジションのイテレーター
    auto firstPosIte = firstPosList[racerNum];
    Player* newPlayer = new Player(firstPosIte);
    std::string str;
    ObjectSubject* subject = newPlayer->GetSubject();
    return newPlayer;
}
CPU* RacerGenerater::CreateRacer(int racerNum)
{
    std::vector<VECTOR> firstPosList = GetGeneratePos::CSVConvertPosition(firstPosPass, 1);
    //ポジションのイテレーター
    auto firstPosIte = firstPosList[racerNum];
    CPU* newPlayer = new CPU(firstPosIte);
    return newPlayer;
}