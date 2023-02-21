#pragma once
#include <list>
#include "Racer.h"
class RacerGenerater
{
public:
    RacerGenerater() {};
    RacerGenerater(int racerNum);
    std::list<Racer*> GetRacerList();
private:
    std::list<Racer*> racerList;
};

