#pragma once
#include "Actor.h"
#include "DxLib.h"
/// <summary>
/// 加速床
/// </summary>
class AccelerationFloor :
    public Actor
{
public:
    AccelerationFloor();
    /// <summary>
    /// 加速床の場所と方向
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="angularY"></param>
    AccelerationFloor(VECTOR pos, VECTOR angularY);
    ~AccelerationFloor();
    /// <summary>
    /// 更新
    /// </summary>
    void Update() override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;
private:
    // 加速度
    const float addAccel = 50.0f;
    //　半径
    const float setRadius = 27.0f;
    //大きさ
    const float setScale = 5.0f;
    //エフェクト　（本体）
    int effekseerModelHandle;
    //d
    int playingEffect;
};