#pragma once
#include "DxLib.h"
#include "Object.h"
/// <summary>
/// 当たり判定で使う引数にして渡したい情報
/// </summary>
struct HitCheckExamineObjectInfo
{
    VECTOR pos = {};//ポジション
    float radius = 0;//半径
};