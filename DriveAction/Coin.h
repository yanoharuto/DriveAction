#pragma once
#include <string>
#include "Actor.h"
#include "SphereCollider.h"
class Coin :
    public Actor
{
public:
    Coin();
    /// <summary>
    /// 初期位置を教えて
    /// </summary>
    /// <param name="firstPos"></param>
    Coin(VECTOR firstPos);
    ~Coin();
    /// <summary>
    /// 更新
    /// </summary>
    void Update()override;
    /// <summary>
    /// ぶつかった時の処理
    /// </summary>
    /// <param name="conflictInfo"></param>
    void ConflictProccess(const ConflictExamineResultInfo conflictInfo);
private:
    //毎秒向きがこの値分変化する
    static const float rotateY;
    //縦方向に移動する量
    static const float moveYValue;
    //縦方向に移動する速度
    static const float moveYSpeed;
    //半径
    static const float setRadius;
    //エフェクトの大きさ
    static const float effectSize;
    //最初の高さ
    static const float firstY;
    //エフェクトのパス
    static const std::string coinEffectPass;
    //modelのパス
    static const std::string coinPass;
    //コインの効果音のパス
    static const std::string coinSEPass;
    //回転量
    float totalMoveYValue = 0;
    //車にぶつかった時のエフェクト
    int conflictEffect=-1;
    //球当たり判定
    SphereCollider* collider;
};

