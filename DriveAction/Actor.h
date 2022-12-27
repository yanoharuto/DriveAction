#pragma once
#include "Object.h"
class Actor :
    public Object
{
public:
    Actor() 
        :modelHandle(-1),
        direction({}),
        velocity({})
    {
    };
    virtual ~Actor()
    {
    };
    /// <summary>
    /// �X�V
    /// </summary>
    virtual void Update(const float deltaTime) {};
    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw() {};
    /// <summary>
    /// �Փˏ���
    /// </summary>
    /// <param name="tag">�Փ˂�������</param>
    virtual void ConflictProcess() {};
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
    // </summary>
    /// <returns></returns>
    const VECTOR& GetVelocity() const
    {
        return velocity;
    }
protected:
    //�`�惂�f��
    int modelHandle;
    //���x
    VECTOR velocity;
    //����
    VECTOR direction;

};

