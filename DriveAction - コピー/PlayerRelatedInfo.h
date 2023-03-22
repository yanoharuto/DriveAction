#pragma once
#include "DxLib.h"
#include "ItemTag.h"
/// <summary>
/// プレイヤーのUI周りに必要な情報
/// </summary>
struct  PlayerRelatedInfo
{
    //何周したか
    int lap;
    //順位
    int rank;
    //車が逆走していたら
    bool reverse;
    //持っているアイテム
    ItemTag itemTag;
    //時間
    float time;
    //速度
    float accelPower;
    //最大速度に対する現在の速度の割合
    float accelPowerParcent;
};