#pragma once
#include "DxLib.h"
enum class ObjectTag
{
    car,
    enemy,
    enemyAttack,
    obstacle,
    stage,
    goal
};
/// <summary>
/// 当たり判定で使う引数にして渡したい情報
/// </summary>
struct ArgumentConflictInfo
{
    bool hitFlag = false;
    ObjectTag tag = ObjectTag::obstacle;
    VECTOR pos = {};
    float radius = 0;
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
        direction({}),
        position({}),
        tag(ObjectTag::car),
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
    /// <summary>
    /// objectの半径
    /// </summary>
    /// <returns></returns>
    const float GetRadius()
    {
        return radius;
    }
    /// <summary>
/// 向き所得
/// </summary>
/// <returns></returns>
    const VECTOR& GetDir() const
    {
        return direction;
    };
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
    //方向
    VECTOR direction;
};

