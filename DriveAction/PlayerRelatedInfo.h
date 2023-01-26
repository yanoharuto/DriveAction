#pragma once
#include "DxLib.h"
struct  PlayerRelatedInfo
{
    int lap;
    int rank;
    VECTOR carDirection;
    VECTOR nextCheckPointDirection;
    float time;
    float accelPower;
};