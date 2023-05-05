#pragma once
#include <string>
#include "DamageObject.h"
class LineCollider;
enum EffectKind;
enum Init::InitObjKind;
struct InitParam
{
    EffectKind laserEffectPass;
    Init::InitObjKind initKind;
    float laserSize;
    float trackSize;
    float radius;
    float laserRange;
};
/// <summary>
/// 回転レーザー
/// </summary>
class RotatingLasers abstract :public DamageObject
{
public:
    /// <summary>
    /// 回転レーザー
    /// </summary>
    /// <param name="carInfo"></param>
    /// <param name="timer"></param>
    RotatingLasers(InitParam setParam, ObjectObserver* setObserver);
    ~RotatingLasers();
    void RotateLaser(EffectKind kind,float rotaSpeed, float laserRange);
    void SetLaserTrack();
    void Draw()override;
protected:

    static const EffectKind laserTrackPass;
    
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

    VECTOR endPos = {};
    LineCollider* collider;
};