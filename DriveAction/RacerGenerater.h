#pragma once
#include <string>
#include "Racer.h"
#include "Player.h"
#include "CarModelEnum.h"
class RacerGenerater
{
public:
    RacerGenerater();
    void CreateRacers(int racerNum, std::list<Racer*>* racerList,Player** player);
private:
    std::string carModelAddress[CAR_MODEL_ENUM_SIZE];
};

