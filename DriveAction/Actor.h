#pragma once
#include "Object.h"
#include "ConflictExamineResultInfo.h"
#include "ArgumentConflictResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "HitChecker.h"
#include "OriginalMath.h"
/// <summary>
/// �`�悷��I�u�W�F�N�g
/// </summary>
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
            //�ύX�O�̍s���ۑ�
            MATRIX tmpMat = MV1GetMatrix(modelHandle);
            //������ς���
            ModelSetMatrix();
            //�|�W�V�����ύX
            UpdateMV1Pos();
            //�T�C�Y�ύX
            MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));
            MV1DrawModel(modelHandle);
            //�s������ɖ߂�
            MV1SetRotationMatrix(modelHandle, tmpMat);
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
    /// <summary>
    /// �����蔻��œ������Ă���n�����
    /// </summary>
    /// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitCheckExamineInfo()
    {
        HitCheckExamineObjectInfo objInfo;
        objInfo.SetExamineInfo(this);
        objInfo.velocity = velocity;
        return objInfo;
    };

protected:
    /// <summary>
    /// ���̃I�u�W�F�N�g�ɓ������Ă邩���ׂ�p�̏��
    /// </summary>
    /// <returns></returns>
    ArgumentConflictResultInfo GetConflictArgumentInfo()
    {
        ArgumentConflictResultInfo resultInfo;
        resultInfo.SetObjInfo(this);
        return resultInfo;
    };
    /// <summary>
    /// �`�惂�f���̍s����Z�b�g
    /// </summary>
    virtual void ModelSetMatrix()
    {
        // �����ɍ��킹�ĉ�].
        MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        
        MATRIX tmpMat = MV1GetMatrix(modelHandle);
        // ���f���Ɍ����Ăق��������ɉ�].
        MATRIX rotYMat = MGetRotY(180.0f * RAGE);
        tmpMat = MMult(tmpMat, rotYMat);
        MV1SetRotationMatrix(modelHandle, tmpMat);
    }
    //�|�W�V�����̈ʒu�ɕύX����
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
    //model�̃T�C�Y
    float modelSize = 1;
};