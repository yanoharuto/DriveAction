#pragma once
#include "SphereCollider.h"
#include "Actor.h"
//岩のパターン　大きさとかが変わる
#define RockPattern 3
/// <summary>
/// 岩
/// </summary>
class Rock :
    public Actor
{
public:
    /// <summary>
    /// 岩　3パターンの岩がある
    /// </summary>
    /// <param name="setPos"></param>
    /// <param name="pattern"></param>
    Rock(VECTOR setPos,int pattern);
    /// <summary>
    /// 当たり判定を消す
    /// </summary>
    ~Rock();
private:
    //modelのパス
    static const std::string modelPass[RockPattern];
    //ぶつかった時に付き飛ばす力
    static const int setBouncePower;
    //当たり判定の幅
    static const float setRadius[RockPattern]; 
    //大きさ
    VECTOR scale;
    //球当たり判定
    SphereCollider* collider;
};

