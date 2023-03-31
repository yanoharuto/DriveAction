#pragma once
#include<string>
#include "Actor.h"
#include "ItemArgumentCarInfo.h"
#include "DxLib.h"
#include "SphereCollider.h"
/// <summary>
/// �ォ�牺�ɗ��Ƃ����e
/// </summary>
class Rocket final :public Actor
{
public:
    Rocket() {};
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="carInfo"></param>
    Rocket(ItemArgumentCarInfo carInfo);
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
    static const std::string effectPass;
    //�ŏ��̗������x
    static const float setFallingSpeed;
    //�������x
    float fallingSpeed = setFallingSpeed;
    //�͂����Ԃ���
    static const float setBouncePower;
    //�d��
    static const float gravityPower;
    //���P�b�g�̃T�C�Y
    static const float setModelSize;
    //�G�t�F�N�g�̃T�C�Y
    static const float setEffectSize;
    //�����蔻��̑傫��
    static const float setRadius;
    //�R�������̓����蔻��̑傫��
    static const float setBurnRadius;
    //�����Ă���G�t�F�N�g
    int burnEffect = -1;
    //�n�ʂɐG��Ă��邩
    bool onGround = false;
    //�����蔻��
    SphereCollider* collider = nullptr;
};