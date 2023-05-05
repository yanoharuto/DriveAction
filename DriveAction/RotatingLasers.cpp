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

//�ŏ��̉�]����
const VECTOR RotatingLasers::firstDir = { 0.0f,0.0f,-1.0f };


/// <summary>
/// ������
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
    //�����ύX�@�G�t�F�N�g�̌�����ς���
    direction = VNorm(OriginalMath::GetYRotateVector(direction, rotaSpeed));
    effectRota -= rotaSpeed * RAGE;
    //���[�U�[�̏I���_
    endPos = VAdd(position, VScale(direction, position.y * laserRange));
    //�G�t�F�N�g�I�������������񌂂�
    if (laserEffect == -1)
    {
        laserEffect = EffectManager::GetPlayEffect3D(kind);
    }
    //�G�t�F�N�g�̌����Ƃ��ꏊ���C��
    SetPosPlayingEffekseer3DEffect(laserEffect, position.x, position.y, position.z);
    SetRotationPlayingEffekseer3DEffect(laserEffect, 0, effectRota, 0);

    SetLaserTrack();
    isDrawShadow = false;
}
/// <summary>
/// ���[�U�[���������ꏊ�Ɍ���o��
/// </summary>
void RotatingLasers::SetLaserTrack()
{
    //���[�U�[�Ղ̃G�t�F�N�g���\�����I������
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
