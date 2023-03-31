#pragma once
#include <string>
#include "ItemArgumentCarInfo.h"
#include "Actor.h"
#include "Timer.h"
#include "LineCollider.h"
#include "FiringObjOwner.h"
struct InitParam
{
    std::string laserEffectPass;
    float laserSize;
    float trackSize;
    float radius;
    float laserRange;
};
/// <summary>
/// 回転レーザー
/// </summary>
class RotatingLasers abstract :public Actor
{
public:
    /// <summary>
    /// 回転レーザー
    /// </summary>
    /// <param name="carInfo"></param>
    /// <param name="timer"></param>
    RotatingLasers(FiringObjOwner* setOwner,InitParam setParam);
    ~RotatingLasers();
    void RotateLaser(std::string laserEffectPass,float rotaSpeed, float laserRange);
    void SetLaserTrack();
    void Draw()override;
protected:

    static const std::string laserTrackPass;
    
    static const std::string laserSEPass;
    
    //エフェクトハンドル
    int laserEffect = -1;
    //焼き後
    int trackEffect = -1;
    //エフェクトのシャドウになるカプセルを描画したか
    bool isDrawShadow = false;
    //エフェクトの回転角（ラジアン）
    float effectRota;
    //最初の回転方向
    static const VECTOR firstDir;

    FiringObjOwner* owner;
    VECTOR endPos = {};
    LineCollider* collider;
};