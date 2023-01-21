#pragma once
#include "DxLib.h"

/// <summary>
/// 車の周辺情報を調べるのに必要
/// </summary>
struct  CarNeighborhoodExamineInfo
{
    VECTOR pos;//探索開始位置位置
    float range;//探索範囲
};