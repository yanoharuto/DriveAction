#pragma once
struct CircuitData
{
    //車が次に行くべき行き先が書いてある
    std::vector<VECTOR> positionVec;
    //逆走してゴールしないように方向も乗せる
    std::vector<VECTOR> directionVec;
};