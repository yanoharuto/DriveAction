#pragma once
#include "DxLib.h"

/// <summary>
/// 車の周辺情報を調べるときに使う
/// </summary>
struct  CarNeighborhoodExamineInfo
{
    VECTOR pos, dir;//車の位置と車の向き
    float range;//探索範囲
};