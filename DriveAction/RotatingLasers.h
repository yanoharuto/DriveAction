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
/// ��]���[�U�[
/// </summary>
class RotatingLasers abstract :public DamageObject
{
public:
    /// <summary>
    /// ��]���[�U�[
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
    
    //�G�t�F�N�g�n���h��
    int laserEffect = -1;
    //�Ă���
    int trackEffect = -1;
    //�G�t�F�N�g�̃V���h�E�ɂȂ�J�v�Z����`�悵����
    bool isDrawShadow = false;
    //�G�t�F�N�g�̉�]�p�i���W�A���j
    float effectRota;
    //�ŏ��̉�]����
    static const VECTOR firstDir;

    VECTOR endPos = {};
    LineCollider* collider;
};