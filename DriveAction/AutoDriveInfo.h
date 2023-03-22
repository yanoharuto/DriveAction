#pragma once
#include "DxLib.h"
/// <summary>
/// 自動運転のために必要なパラメーター
/// </summary>
struct AutoDriveInfo
{
    float turnProccessLine;
    VECTOR position;
    VECTOR direction;
};