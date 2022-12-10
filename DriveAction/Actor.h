#pragma once
#include "DxLib.h"

class Actor
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <returns></returns>
    Actor()
        :AliveFlag(true),
        Position({}),
        Velocity({}),
        Direction({})
    {
    };
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <returns></returns>
    virtual ~Actor() {};
    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update() {};
    /// <summary>
    /// 描画
    /// </summary>
    virtual void Draw() {};
    /// <summary>
    /// 現在動けるかどうか
    /// </summary>
    /// <returns></returns>
    bool GetAliveFlag()
    {
        return AliveFlag;
    }
protected:
    //描画モデル
    int ModelHandle;
    //場所
    VECTOR Position;
    //速度
    VECTOR Velocity;
    //方向
    VECTOR Direction;
    //生存フラグ
    bool AliveFlag;
};

