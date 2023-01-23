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
    const bool GetAliveFlag() const
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
    /// object�̔��a
    /// </summary>
    /// <returns></returns>
    const float GetRadius()
    {
        return radius;
    }
    const float GetBouncePower()
    {
        return bouncePower;
    }
    /// <summary>
/// ��������
/// </summary>
/// <returns></returns>
    const VECTOR& GetDir() const
    {
        return direction;
    };
    /// <summary>
    /// �����̃^�O��Ԃ�
    /// </summary>
    /// <returns></returns>
    const ObjectTag GetTag()
    {
        return tag;
    };
protected:
    float bouncePower;
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

