#pragma once
#include "DxLib.h"
#include "ItemTag.h"
/// <summary>
/// ƒvƒŒƒCƒ„[ü‚è‚Ìî•ñ
/// </summary>
struct  PlayerRelatedInfo
{
    int lap;
    int rank;
    VECTOR carDirection;
    VECTOR nextCheckPointDirection;
    ItemTag itemTag;
    float time;
    float accelPower;
};