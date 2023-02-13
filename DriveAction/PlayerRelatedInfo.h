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
    //車の向き
    VECTOR carDirection;
    //車の次に向かう場所の向き
    VECTOR nextCheckPointDirection;
    //持っているアイテム
    ItemTag itemTag;
    //時間
    float time;
    //速度
    float accelPower;
};