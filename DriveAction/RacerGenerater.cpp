#include "RacerGenerater.h"
#include "CPU.h"
#include "CourceDataLoader.h"

RacerGenerater::RacerGenerater()
{
}
void RacerGenerater::CreateRacers(int racerNum, std::list<Racer*>* racerList, Player** player, PlayerInformationCenter* infoCenter)
{
    std::list<VECTOR> firstPosList = CourceDataLoader::GetVECTORData(firstPosPass);
    //ポジションのイテレーター
    auto firstPosIte = firstPosList.begin();
    
    //レーサーの数だけNewする
    Racer* newRacer;
    for (int i = 0; i < racerNum + 1; i++)
    {
        if (i == 0)
        {
            (*player) = new Player(*firstPosIte);
            newRacer =(*player);
            infoCenter->AddPlayer((*player));
        }
        else
        {
            newRacer = new CPU(*firstPosIte);
        }
        (*racerList).push_front(newRacer);
        firstPosIte++;
    }

}