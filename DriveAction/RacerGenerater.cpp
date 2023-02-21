#include "RacerGenerater.h"
#include "Player.h"
#include "CPU.h"
#include "CourceDataLoader.h"
RacerGenerater::RacerGenerater(int racerNum)
{
    std::list<VECTOR> firstPosList = CourceDataLoader::GetCarFirstPosList();
    //最初の一行は向く方向なので消す
    firstPosList.erase(firstPosList.begin());
    //ポジションのイテレーター
    auto firstPosIte = firstPosList.begin();
    Racer* newRacer;
    //レーサーの数だけNewする
    for (int i = 0; i < racerNum + 1; i++)
    {
        firstPosIte++;
        if (i == 0)
        {
            newRacer = new Player(*firstPosIte);
        }
        else
        {
            newRacer = new CPU(*firstPosIte);
        }
        racerList.push_front(newRacer);
    }
}

std::list<Racer*> RacerGenerater::GetRacerList()
{
    return racerList;
}
