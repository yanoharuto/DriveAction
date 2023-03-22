#pragma once
#include <string>
#include "ItemArgumentCarInfo.h"
#include "Actor.h"
#include "Timer.h"
#include "SphereCollider.h"
#include "FiringObjOwner.h"
/// <summary>
/// ��]���[�U�[
/// </summary>
class RotatingLasers :public Actor
{
public:
    /// <summary>
    /// ��]���[�U�[
    /// </summary>
    /// <param name="carInfo"></param>
    /// <param name="timer"></param>
    RotatingLasers(FiringObjOwner* setOwner);
    ~RotatingLasers();
    /// <summary>
    /// ��]������
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(float deltaTime)override;

private:
    //���[�U�[�G�t�F�N�g�̃p�X
    const std::string laserEffectAddress = "Lacer.efkefc";
    //�G�t�F�N�g�n���h��
    int playEffect = -1;
    //�G�t�F�N�g�̉�]�p�i���W�A���j
    float effectRota;
    //�ŏ��̉�]����
    static const VECTOR firstDir;
    //��]���x
    static const float rotaSpeed;
    //���[�U�[�̒��S����̋���
    static const float laserRange;
    //���[�U�[�̑���
    static const float setRadius;
    //�����鍂�x
    static const float conflictY;
    //�����������̂͂�����
    static const float setBouncePower;
    FiringObjOwner* owner;
    VECTOR firstPos = {};
    SphereCollider* collider;
};