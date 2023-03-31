#pragma once
#include <string>
#include "Racer.h"
#include "PlayerInformationCenter.h"
class RacerGenerater
{
public:
    RacerGenerater();
    void CreateRacers(int racerNum, std::list<Racer*>* racerList,Player** player,PlayerInformationCenter* infoCenter);
private:
    const std::string firstPosPass = "/firstPosition.txt";
};

