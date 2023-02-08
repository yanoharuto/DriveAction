#pragma once
#include "DxLib.h"
#include "ItemTag.h"
/// <summary>
/// プレイヤー周りの情報
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