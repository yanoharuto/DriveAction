#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "SoundPlayer.h"
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
    virtual void Draw() =0;

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