#pragma once
#include "PlayerRelatedInfo.h"
#include "Timer.h"
class RaceScreen
{
public:
    RaceScreen();
    ~RaceScreen();
    void SetUp();
    static int GetRaceScreen();
private:
   static int screen;
   };

