#pragma once
#include "CarParamater.h"
#include "ItemTag.h"
#include "DxLib.h"
/// <summary>
/// 空を飛ぶ船の情報
/// 生存時間　爆弾発射クールタイム　最大高度　上昇速度
/// </summary>
struct FlyShipArgumentInfo
{
    //生存時間
    float setAliveTime;
    //発射のクールタイム
    float setCoolTime;
    //最大高度
    float maxHeight;
    //上昇速度
    float addUpSpeed;
};