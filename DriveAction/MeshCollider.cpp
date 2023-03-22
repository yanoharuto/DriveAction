#include "MeshCollider.h"
#include "ConflictManager.h"
MeshCollider::MeshCollider(int setModelHandle, ConflictExamineResultInfo setResultInfo)
{
    modelHandle = setModelHandle;
    tag = setResultInfo.tag;
    bouncePower = setResultInfo.bouncePower;
    ConflictManager::AddConflictObjInfo(this);
}

MeshCollider::~MeshCollider()
{
}

ConflictExamineResultInfo MeshCollider::HitCheck(HitCheckExamineObjectInfo examinInfo)
{
    return GetSphereConflictModelInfo(examinInfo);
}


/// <summary>
/// MV1CollCheck_Sphere���g���ă��f���n���h�����˒��������ׂ��
/// </summary>
/// <param name="modelHandle">���ׂ郂�f��</param>
/// <param name="examineInfo">���ׂ邽�߂ɕK�v�ȏ��</param>
/// <returns>�Ԃ������ʒu��Ԃ���B�Ԃ����ĂȂ��Ȃ�HitFlag��false</returns>
ConflictExamineResultInfo MeshCollider::GetSphereConflictModelInfo(HitCheckExamineObjectInfo examineInfo) 
{
    DxLib::MV1_COLL_RESULT_POLY_DIM polyDimInfo = MV1CollCheck_Sphere(modelHandle, -1, examineInfo.pos, examineInfo.radius);
    VECTOR bounceVec = {};
    VECTOR nowPos = examineInfo.pos;
    bool hitFlag = false;
    ConflictExamineResultInfo resultInfo;
    resultInfo.tag = tag;
    resultInfo.bouncePower = bouncePower;
    //model�ɂԂ����Ă��邩
    if (polyDimInfo.HitNum != 0)
    {
        hitFlag = true;
        //������Ȃ��ʒu�Ɉړ�����܂ŏ���
        while (hitFlag && fabsf(VSize(examineInfo.velocity)) > 0)
        {
            //�|���S���̐�����������΂�
            for (int i = 0; i < polyDimInfo.HitNum; i++)
            {
                MV1_COLL_RESULT_POLY polyInfo = polyDimInfo.Dim[i];//�|���S���̒��_���
                float a = -VDot(VNorm(examineInfo.velocity), polyInfo.Normal);//�@������͂������傫�����o��
                //�͂������x�N�g��
                bounceVec = VSub(examineInfo.velocity, VScale(polyInfo.Normal, a));
                //�͂������̃|�W�V����
                nowPos = VAdd(nowPos, bounceVec);
            }
            MV1CollResultPolyDimTerminate(polyDimInfo);//��x�|���S����������
            //������x�������Ă��镔�������邩���ׂ�
            polyDimInfo = MV1CollCheck_Sphere(modelHandle, -1, nowPos, examineInfo.radius);
            //�����������ĂȂ�������I��
            hitFlag = polyDimInfo.HitNum != 0;
        }
        //�ŏI�I��BouncePower��������΂�
        resultInfo.hitFlag = true;
        resultInfo.bounceVec = VScale(VNorm(VSub(examineInfo.pos, nowPos)), resultInfo.bouncePower);
        resultInfo.pos = nowPos;
        //�㏈��
        MV1CollResultPolyDimTerminate(polyDimInfo);
        return  resultInfo;
    }
    MV1CollResultPolyDimTerminate(polyDimInfo);
    return resultInfo;
}

HitCheckExamineObjectInfo MeshCollider::GetHitExamineCheckInfo()
{
    return { {},{},0};
}

void MeshCollider::ConflictProccess(ConflictExamineResultInfo resultInfo)
{
}
