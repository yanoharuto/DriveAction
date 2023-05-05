#pragma once
#include<string>
#include "DxLib.h"
#include "DamageObject.h"
enum EffectKind;
class SphereCollider;
/// <summary>
/// �ォ�牺�ɗ��Ƃ����e
/// </summary>
class Rocket final :public DamageObject
{
public:
    Rocket(ObjectObserver* setObserver);
    ~Rocket();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update()override;
    /// <summary>
    /// �Փˌ�̏���
    /// </summary>
    void ConflictProccess(ConflictExamineResultInfo resultInfo)override;
private:
    //���P�b�g�̃��f���̃A�h���X
    static const std::string rocketModelPass;
    //�G�t�F�N�g��model�̃A�h���X
    static const EffectKind effectPass;
    //�ŏ��̗������x
    static const float setFallingSpeed;
    //�������x
    float fallingSpeed = setFallingSpeed;
    //�d��
    static const float gravityPower;
    //�R�������̓����蔻��̑傫��
    static const float setBurnRadius;
    //�R���Ă���Ƃ��̃G�t�F�N�g
    int burnEffect = -1;
    //�n�ʂɐG��Ă��邩
    bool onGround = false;
    //�����蔻��
    SphereCollider* collider = nullptr;
};