#include "RotatingLasers.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "SoundPlayer.h"
#include "Timer.h"
#include "LineCollider.h"
const EffectKind RotatingLasers::laserTrackPass = laserTrack;
const std::string RotatingLasers::laserSEPass = "Laser.mp3";

//最初の回転方向
const VECTOR RotatingLasers::firstDir = { 0.0f,0.0f,-1.0f };


/// <summary>
/// 初期化
/// </summary>
/// <param name="setOwner"></param>
RotatingLasers::RotatingLasers(InitParam setParam, ObjectObserver* setObserver)
    :DamageObject(setParam.initKind, setObserver)
{
    tag = ObjectTag::damageObject;
    
    EffectManager::LoadEffectManager(setParam.laserEffectPass);
    
    EffectManager::LoadEffectManager(laserTrackPass);
    direction = firstDir;
    radius = setParam.radius;
    collider = new LineCollider(this,setParam.laserRange);

}

RotatingLasers::~RotatingLasers()
{
    StopEffekseer3DEffect(laserEffect);
    DeleteEffekseerEffect(laserEffect);
    StopEffekseer3DEffect(trackEffect);
    DeleteEffekseerEffect(trackEffect);
    ConflictManager::EraceConflictObjInfo(collider);
    SAFE_DELETE(collider);
}

void RotatingLasers::RotateLaser(EffectKind kind, float rotaSpeed, float laserRange)
{
    position = observer->GetSubPos();
    //方向変更　エフェクトの向きを変える
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    effectRota -= rotaSpeed * RAGE;
    //レーザーの終着点
    endPos = VAdd(position, VScale(direction, position.y * laserRange));
    //エフェクト終了したらもう一回撃つ
    if (laserEffect == -1)
    {
        laserEffect = EffectManager::GetPlayEffect3D(kind);
    }
    //エフェクトの向きとか場所を修正
    SetPosPlayingEffekseer3DEffect(laserEffect, position.x, position.y, position.z);
    SetRotationPlayingEffekseer3DEffect(laserEffect, 0, effectRota, 0);

    SetLaserTrack();
    isDrawShadow = false;
}
/// <summary>
/// レーザーを撃った場所に後を出す
/// </summary>
void RotatingLasers::SetLaserTrack()
{
    //レーザー跡のエフェクトが表示し終えたら
    if (IsEffekseer3DEffectPlaying(trackEffect) == -1)
    {
        trackEffect = EffectManager::GetPlayEffect3D(laserTrackPass);
    }
    SetPosPlayingEffekseer3DEffect(trackEffect, endPos.x, 0, endPos.z);
}
void RotatingLasers::Draw()
{
    if (!isDrawShadow)
    {
        DrawCapsule3D(position, endPos, radius, 4, GetColor(0, 0, 0), GetColor(0, 0, 0), true);
        isDrawShadow = true;
    }
}
