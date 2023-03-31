#include "RotatingLasers.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
#include "Utility.h"
#include "SoundPlayer.h"
const std::string RotatingLasers::laserTrackPass = "LaserTrack.efkefc";
const std::string RotatingLasers::laserSEPass = "Laser.mp3";

//最初の回転方向
const VECTOR RotatingLasers::firstDir = { 0.0f,0.0f,-1.0f };


/// <summary>
/// 初期化
/// </summary>
/// <param name="setOwner"></param>
RotatingLasers::RotatingLasers(FiringObjOwner* setOwner,InitParam setParam)
{
    position = setOwner->GetPosition();
    owner = setOwner;
    tag = ObjectTag::damageObject;
    
    EffectManager::LoadEffectManager(setParam.laserEffectPass, setParam.laserSize);
    
    EffectManager::LoadEffectManager(laserTrackPass, setParam.trackSize);
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

void RotatingLasers::RotateLaser(std::string laserEffectPass,float rotaSpeed,float laserRange)
{
    position = owner->GetPosition();
    //方向変更　エフェクトの向きを変える
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    effectRota -= rotaSpeed * RAGE;
    endPos = VAdd(position, VScale(direction, position.y * laserRange));
    if (owner->GetOwnerState() != OwnerState::Delete)
    {
        if (laserEffect == -1)
        {
            laserEffect = EffectManager::GetPlayEffect3D(laserEffectPass);
        }
        SetPosPlayingEffekseer3DEffect(laserEffect, position.x, position.y, position.z);
        SetRotationPlayingEffekseer3DEffect(laserEffect, 0, effectRota, 0);
        SetLaserTrack();
        SetPosPlayingEffekseer3DEffect(trackEffect, endPos.x, 0, endPos.z);

        isDrawShadow = false;
    }
    else
    {
        if (laserEffect != -1)
        {
            StopEffekseer3DEffect(trackEffect);
            trackEffect = -1;
            StopEffekseer3DEffect(laserEffect);
            laserEffect = -1;
        }
    }
}

void RotatingLasers::SetLaserTrack()
{
    //レーザー跡のエフェクトが表示し終えたら
    if (IsEffekseer3DEffectPlaying(trackEffect) == -1)
    {
        trackEffect = EffectManager::GetPlayEffect3D(laserTrackPass);
    }
}
void RotatingLasers::Draw()
{
    if (!isDrawShadow)
    {
        DrawCapsule3D(position, endPos, radius, 4, GetColor(0, 0, 0), GetColor(0, 0, 0), true);
        isDrawShadow = true;
    }
}
