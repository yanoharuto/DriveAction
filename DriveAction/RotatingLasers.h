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
/// ��]���[�U�[
/// </summary>
class RotatingLasers abstract :public Actor
{
public:
    /// <summary>
    /// ��]���[�U�[
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

    FiringObjOwner* owner;
    VECTOR endPos = {};
    LineCollider* collider;
};