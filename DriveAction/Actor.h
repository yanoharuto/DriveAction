#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "HitChecker.h"
#include "OriginalMath.h"
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
    virtual void Update() {};
    /// <summary>
    /// �`��
    /// </summary>
    virtual void Draw()
    {
        if (modelHandle != - 1)
        {
            ModelSetMatrix();
            UpdateMV1Pos();
            MV1DrawModel(modelHandle);
        }
    }
    
    /// <summary>
    /// �Փˏ���
    /// </summary>
    virtual void ConflictProccess(const ConflictExamineResultInfo conflictInfo) {};
    /// <summary>
    /// ���x����
    // </summary>
    /// <returns></returns>
    VECTOR GetVelocity()
    {
        return velocity;
    }
    virtual HitCheckExamineObjectInfo GetHitCheckExamineInfo()
    {
        HitCheckExamineObjectInfo objInfo;
        objInfo.SetExamineInfo(this);
        objInfo.velocity = velocity;
        return objInfo;
    };
protected:
    
    ArgumentConflictResultInfo GetConflictArgumentInfo()
    {
        ArgumentConflictResultInfo resultInfo;
        resultInfo.SetObjInfo(this);
        return resultInfo;
    };
    virtual void ModelSetMatrix()
    {
        // �����ɍ��킹�ĉ�].
        MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        // ���f���Ɍ����Ăق��������ɉ�].
        MATRIX tmpMat = MV1GetMatrix(modelHandle);
        MATRIX rotYMat = MGetRotY(180.0f * RAGE);
        tmpMat = MMult(tmpMat, rotYMat);
        MV1SetRotationMatrix(modelHandle, tmpMat);
    }
    virtual void UpdateMV1Pos()
    {
        // �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
        if (VSize(velocity) != 0)
        {
            direction = VNorm(velocity);
        }
        // �|�W�V�������X�V.
        position = VAdd(position, velocity);
        // �RD���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, position);
    }
    //�`�惂�f��
    int modelHandle;
    //���x
    VECTOR velocity;
};