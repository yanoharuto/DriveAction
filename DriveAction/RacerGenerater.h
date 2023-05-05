#pragma once
#include <string>


class Player;
class CPU;
class RacerGenerater
{
public:
    RacerGenerater();
    Player* CreatePlayer(int racerNum);
    CPU* CreateRacer(int racerNum);
private:
    const std::string firstPosPass = "data/stageMap_playerPos.csv";
};

