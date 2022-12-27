#pragma once
#include "DxLib.h"
enum class ObjectTag
{
    player,
    CPUCar,
    enemy,
    enemyAttack,
    obstacle,
    stage
};

class Object
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <returns></returns>
    Object()
        :aliveFlag(true),
        position({}),
        tag(ObjectTag::player),
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
    const float GetRadius()
    {
        return radius;
    }
    /// <summary>
    /// �����̃^�O��Ԃ�
    /// </summary>
    /// <returns></returns>
    const ObjectTag GetTag()
    {
        return tag;
    };
protected:
    //�ꏊ
    VECTOR position;
    //���a
    float radius;
    //�����t���O
    bool aliveFlag;
    //���������Ȃ̂�
    ObjectTag tag;
};

