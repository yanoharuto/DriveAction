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
        :AliveFlag(true),
        Position({}),
        Velocity({}),
        Direction({})
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
    virtual void Update() {};
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
        return AliveFlag;
    }
protected:
    //�`�惂�f��
    int ModelHandle;
    //�ꏊ
    VECTOR Position;
    //���x
    VECTOR Velocity;
    //����
    VECTOR Direction;
    //�����t���O
    bool AliveFlag;
};

