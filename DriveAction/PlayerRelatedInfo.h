#pragma once
#include "DxLib.h"
/// <summary>
/// �v���C���[����̏��
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