#pragma once
#include "DxLib.h"
#include "ItemTag.h"
/// <summary>
/// �v���C���[����̏��
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