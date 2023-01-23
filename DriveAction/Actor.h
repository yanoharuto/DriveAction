#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
/// <summary>
/// �������̂͑�̂���
/// </summary>
class Actor :
    public Object
{
public:
    Actor() 
        :modelHandle(-1),
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
    virtual void ConflictProcess(float deltaTime, const ConflictExamineResultInfo conflictInfo) {};

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
};