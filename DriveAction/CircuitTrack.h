#pragma once
#include "Stage.h"
class Player;
/// <summary>
/// �R�[�X
/// </summary>
class CircuitTrack final:
    public Stage
{
public:
    /// <summary>
    /// ������
    /// </summary>
    /// <returns></returns>
    CircuitTrack(Player* player);
    
    ///model���f���[�g
    ~CircuitTrack();
    /// <summary>
    /// �R�[�X�̊O���ɓ������Ă邩���ׂ�
    /// </summary>
    /// <param name="actor">�O���ɂ��邩���ׂ�������</param>
    /// <returns>�R�[�X�̊O���ɂ���Ȃ�True</returns>
    bool GetOutsideHitFlag(Actor* actor);
    /// <summary>
    /// �R�[�X�̕ǂɂԂ����Ă邩���ׂ�
    /// </summary>
    /// <param name="Actor">�Ԃ����Ă邩���ׂ�������</param>
    /// <returns>�Ԃ����Ă���True</returns>
    bool GetGurdHitFlag(Actor* Actor);
    /// <summary>
    /// �R�[�X�̃��f����`��
    /// </summary>
    void Draw();
private:
    //�R���W������Y�̕�����
    const int setupYDivNum = 8;
    //�R�[�X�̑傫��
    const float courceModeScaleValue = 0.15f;
    //�R�[�X�̊O���̑傫��
    const float outsideModelScaleValue = 0.15f;
    //�R�[�X�̈ʒu�T���Ɏg�������̎n�_
    const float sY = 0;
    //�R�[�X�̈ʒu�T���Ɏg�������̏I�_
    const float eY = -11;
    //�R�[�X��model
    int courceModelHandle;
    //�R�[�X�̊O����model
    int outsideModelHandle;
    //�R�[�X�̊O����model�̃|�W�V����
    VECTOR outsideModelPosition = { 0,-8,0 };
};

