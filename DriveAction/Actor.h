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
        :aliveFlag(true),
        modelHandle(-1),
        position({}),
        velocity({}),
        direction({})
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
    virtual void Update(const float deltaTime) {};
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
        return aliveFlag;
    };
    /// <summary>
    /// ポジション所得
    /// </summary>
    /// <returns></returns>
    const VECTOR& GetPos()const
    {
        return position;
    };
    /// <summary>
    /// 向き所得
    /// </summary>
    /// <returns></returns>
    const VECTOR& GetDir() const
    {
        return direction;
    };
        /// <summary>
    /// 速度所得
    /// </summary>
    /// <returns></returns>
    const VECTOR& GetVelocity() const
    {
        return velocity;
    };

protected:
    //描画モデル
    int modelHandle;
    //場所
    VECTOR position;
    //速度
    VECTOR velocity;
    //方向
    VECTOR direction;
    //生存フラグ
    bool aliveFlag;
};

