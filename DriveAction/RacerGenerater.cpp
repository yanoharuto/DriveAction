#include <string>
#include "RacerGenerater.h"
#include "CPU.h"
#include "CourceDataLoader.h"
#include "EnumToString.h"
#include "AssetManager.h"
RacerGenerater::RacerGenerater()
{
    carModelAddress[0] = "BlueBull.mv1";
    carModelAddress[1] = "IceBlades.mv1";
    carModelAddress[2] = "PrototypeZero.mv1";
    carModelAddress[3] = "Rocker.mv1";
    carModelAddress[4] = "Tanker.mv1";
}
void RacerGenerater::CreateRacers(int racerNum, std::list<Racer*>* racerList, Player** player)
{
    std::list<VECTOR> firstPosList = CourceDataLoader::GetCarFirstPosList();
    //ポジションのイテレーター
    auto firstPosIte = firstPosList.begin();
    
    //レーサーの数だけNewする
    Racer* newRacer;
    for (int i = 0; i < racerNum + 1; i++)
    {
        firstPosIte++;
        std::string modelAddress = "data/model/Player/" + carModelAddress[i % CAR_MODEL_ENUM_SIZE];
        if (i == 0)
        {
            (*player) = new Player(*firstPosIte,AssetManager::GetDuplicate3DModelAssetHandle(modelAddress));
            newRacer =(*player);
        }
        else
        {
            newRacer = new CPU(*firstPosIte,AssetManager::GetDuplicate3DModelAssetHandle(modelAddress));
        }
        (*racerList).push_front(newRacer);
    }
}

