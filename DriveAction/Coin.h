#pragma once
#include <string>
#include "Actor.h"
#include "SphereCollider.h"
class Coin :
    public Actor
{
public:
    Coin();
    /// <summary>
    /// �����ʒu��������
    /// </summary>
    /// <param name="firstPos"></param>
    Coin(VECTOR firstPos);
    ~Coin();
    /// <summary>
    /// �X�V
    /// </summary>
    void Update()override;
    /// <summary>
    /// �Ԃ��������̏���
    /// </summary>
    /// <param name="conflictInfo"></param>
    void ConflictProccess(const ConflictExamineResultInfo conflictInfo);
private:
    //���b���������̒l���ω�����
    static const float rotateY;
    //�c�����Ɉړ������
    static const float moveYValue;
    //�c�����Ɉړ����鑬�x
    static const float moveYSpeed;
    //���a
    static const float setRadius;
    //�G�t�F�N�g�̑傫��
    static const float effectSize;
    //�ŏ��̍���
    static const float firstY;
    //�G�t�F�N�g�̃p�X
    static const std::string coinEffectPass;
    //model�̃p�X
    static const std::string coinPass;
    //�R�C���̌��ʉ��̃p�X
    static const std::string coinSEPass;
    //��]��
    float totalMoveYValue = 0;
    //�ԂɂԂ��������̃G�t�F�N�g
    int conflictEffect=-1;
    //�������蔻��
    SphereCollider* collider;
};

