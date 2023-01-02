#pragma once
#include "CircuitTrack.h"
#include "SkyDome.h"
class StageManager
{
public:
    StageManager();
    ~StageManager();
    bool (CircuitTrack::* circuitFanc)(Car* car)const;
    ArgumentConflictInfo (CircuitTrack::* circuitFanc2)(Car* car)const;
private:
    CircuitTrack* circuit;
    SkyDome* skyDome;
};