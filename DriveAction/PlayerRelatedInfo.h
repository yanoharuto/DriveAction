#pragma once
#include "DxLib.h"
/// <summary>
/// プレイヤー周りの情報
/// </summary>
struct  PlayerRelatedInfo
{
    int lap;
    int rank;
    VECTOR carDirection;
    VECTOR nextCheckPointDirection;
    float time;
    float accelPower;
};