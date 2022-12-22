#pragma once
#include "DxLib.h"

class Actor
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <returns></returns>
    Actor()
        :aliveFlag(true),
        modelHandle(-1),
        position({}),
        velocity({}),
        direction({})
    {
    };
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <returns></returns>
    virtual ~Actor() {};
    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update(const float deltaTime) {};
    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw() {};
    /// <summary>
    /// ���ݓ����邩�ǂ���
    /// </summary>
    /// <returns></returns>
    bool GetAliveFlag()
    {
        return aliveFlag;
    };
    /// <summary>
    /// �|�W�V��������
    /// </summary>
    /// <returns></returns>
    const VECTOR& GetPos()const
    {
        return position;
    };
    /// <summary>
    /// ��������
    /// </summary>
    /// <returns></returns>
    const VECTOR& GetDir() const
    {
        return direction;
    };
        /// <summary>
    /// ���x����
    /// </summary>
    /// <returns></returns>
    const VECTOR& GetVelocity() const
    {
        return velocity;
    };

protected:
    //�`�惂�f��
    int modelHandle;
    //�ꏊ
    VECTOR position;
    //���x
    VECTOR velocity;
    //����
    VECTOR direction;
    //�����t���O
    bool aliveFlag;
};

