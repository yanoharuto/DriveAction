#pragma once
#include "DxLib.h"
#include "ObjectTagEnum.h"
class Object
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <returns></returns>
    Object()
        :aliveFlag(true),
        direction({}),
        position({}),
        tag(ObjectTag::car),
        radius(0)
    {
    };
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <returns></returns>
    virtual ~Object() {};

    /// <summary>
    /// ���ݓ����邩�ǂ���
    /// </summary>
    /// <returns></returns>
    bool GetAliveFlag() const
    {
        return aliveFlag;
    };
    /// <summary>
    /// �|�W�V��������
    /// </summary>
    /// <returns></returns>
    VECTOR GetPos()const
    {
        return position;
    };
    /// <summary>
    /// object�̔��a
    /// </summary>
    /// <returns></returns>
    float GetRadius() const
    {
        return radius;
    }

    /// <summary>
    /// ��������
    /// </summary>
    /// <returns></returns>
    VECTOR GetDir() const
    {
        return direction;
    };
    /// <summary>
    /// �����̃^�O��Ԃ�
    /// </summary>
    /// <returns></returns>
    ObjectTag GetTag() const
    {
        return tag;
    };
protected:
    //���a
    float radius;
    //�����t���O
    bool aliveFlag;
    //���������Ȃ̂�
    ObjectTag tag;
    //����
    VECTOR direction;
    //�ꏊ
    VECTOR position;
};

