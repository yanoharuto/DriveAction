#pragma once
#include "DxLib.h"
/// <summary>
/// アップデートがなくていいオブジェクト
/// </summary>
class StaticObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <returns></returns>
    StaticObject()
        :modelHandele(-1),
        position({}),
        scale({})
    {}
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <returns></returns>
    virtual ~StaticObject() {}
    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw() {}
protected:
    int modelHandele;
    VECTOR position;
    VECTOR scale;
};