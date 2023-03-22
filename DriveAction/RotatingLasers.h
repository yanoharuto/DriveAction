#pragma once
#include <string>
#include "ItemArgumentCarInfo.h"
#include "Actor.h"
#include "Timer.h"
#include "SphereCollider.h"
#include "FiringObjOwner.h"
/// <summary>
/// 回転レーザー
/// </summary>
class RotatingLasers :public Actor
{
public:
    /// <summary>
    /// 回転レーザー
    /// </summary>
    /// <param name="carInfo"></param>
    /// <param name="timer"></param>
    RotatingLasers(FiringObjOwner* setOwner);
    ~RotatingLasers();
    /// <summary>
    /// 回転させる
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(float deltaTime)override;

private:
    //レーザーエフェクトのパス
    const std::string laserEffectAddress = "Lacer.efkefc";
    //エフェクトハンドル
    int playEffect = -1;
    //エフェクトの回転角（ラジアン）
    float effectRota;
    //最初の回転方向
    static const VECTOR firstDir;
    //回転速度
    static const float rotaSpeed;
    //レーザーの中心からの距離
    static const float laserRange;
    //レーザーの太さ
    static const float setRadius;
    //当たる高度
    static const float conflictY;
    //当たった時のはじく力
    static const float setBouncePower;
    FiringObjOwner* owner;
    VECTOR firstPos = {};
    SphereCollider* collider;
};