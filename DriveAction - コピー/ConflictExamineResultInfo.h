#pragma once
#include "DxLib.h"
#include "ObjectTagEnum.h"
#include "Object.h"
/// <summary>
/// 当たり判定の結果で出来る情報
/// </summary>
struct ConflictExamineResultInfo
{
    bool hitFlag = false;//当たり判定で当たったか
    ObjectTag tag = ObjectTag::obstacle;//オブジェクトのタグ
    VECTOR pos = {};//当たったオブジェクトのポジション
    VECTOR dir = {};//向いてる方向
    float radius = 0;//半径
    float bouncePower;//反発力
    /// <summary>
    /// 引数のオブジェクトから情報を作成
    /// </summary>
    /// <param name="hit">当たり判定で当たったか</param>
    /// <param name="obj">作りたい情報のオブジェクト</param>
    void SetObjInfo(bool hit,Object* const obj)
    {
        hitFlag = hit;
        tag = obj->GetTag();
        pos = obj->GetPos();
        dir = obj->GetDir();
        radius = obj->GetRadius();
        bouncePower = obj->GetBouncePower();
    }
};