#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "HitChecker.h"

class Actor abstract:
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
    virtual void Draw()
    {
        MV1DrawModel(modelHandle);
    }
    /// <summary>
    /// �����̃I�u�W�F�N�g�ƂԂ����������ׂ�
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="conflictInfo"></param>
    virtual bool HitCheckConflict (const HitCheckExamineObjectInfo examineObjInfo) 
    {
        return  HitChecker::HitCheck(this, examineObjInfo);
    };
    /// <summary>
    /// �Փˏ���
    /// </summary>
    virtual void ConflictProccess() {};
    virtual void ConflictProccess(const ConflictExamineResultInfo conflictInfo) {};
    virtual void ConflictProccess(float deltaTime, const ConflictExamineResultInfo conflictInfo) {};
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