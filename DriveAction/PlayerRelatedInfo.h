#pragma once
#include "DxLib.h"
#include "ItemTag.h"
#include "ObjPosAndDir.h"
/// <summary>
/// プレイヤーのUI周りに必要な情報
/// </summary>
struct  PlayerRelatedInfo
{
    //何周したか
    int lap;
    //順位
    int rank;
    //チェックポイント通過した回数
    int transitCount;
    //当たった回数
    int damageObjHitCount;
    //コインを回収した回数
    int hitCoinCount;
    //車が逆走していたら
    bool isReverseDrive;
    //死んでいるか
    bool isAlive;
    //持っているアイテム
    ItemTag itemTag;
    //経過時間
    float scoreTime;
    //速度
    float accelPower;
    //最大速度に対する現在の速度の割合
    float accelPowerParcent;

    //位置とか方向とか大きさ
    ObjInfo objInfo;
};