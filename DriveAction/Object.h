#pragma once
#include "DxLib.h"
enum class ObjectTag
{
    player,
    CPUCar,
    enemy,
    enemyAttack,
    obstacle,
    stage
};

class Object
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <returns></returns>
    Object()
        :aliveFlag(true),
        position({}),
        tag(ObjectTag::player),
        radius(0)
    {
    };
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <returns></returns>
    virtual ~Object() {};
   
    /// <summary>
    /// 現在動けるかどうか
    /// </summary>
    /// <returns></returns>
    const bool GetAliveFlag() const
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
    const float GetRadius()
    {
        return radius;
    }
    /// <summary>
    /// 自分のタグを返す
    /// </summary>
    /// <returns></returns>
    const ObjectTag GetTag()
    {
        return tag;
    };
protected:
    //場所
    VECTOR position;
    //半径
    float radius;
    //生存フラグ
    bool aliveFlag;
    //自分が何なのか
    ObjectTag tag;
};

