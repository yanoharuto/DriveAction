#pragma once
#include <list>
#include "DxLib.h"
struct CircuitData
{
    //車が次に行くべき行き先が書いてある
    std::list<VECTOR> positionVec;
    //逆走してゴールしないように方向も乗せる
    std::list<VECTOR> directionVec;
};