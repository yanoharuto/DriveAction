#include "CheckPoint.h"
#include "VECTOR3Loader.h"
#include "HitChecker.h"
#include "Utility.h"
#include "ListUtility.h"
#include "OriginalMath.h"
#include "CourceDataLoader.h"
#include "CircuitDataStruct.h"
//�Ԃ�Dir�Ɣ��Ό����Ȃ̂œ��ς������1�ɋ߂�������S�[����������
static const float dirJugeLine = 0.8f;
//���̃`�F�b�N�|�C���g�܂ł̌������o���n�߂�͈�
static const float goalRadius = 150.0f;
//�T�[�L�b�g�̃f�[�^
static CircuitData cPParam;
/// <summary>
/// �f�t�H���g�R���X�g���N�^
/// </summary>
/// <returns></returns>
CheckPoint::CheckPoint()
{
    direction = {};
    vecSize = 0;
    tag = ObjectTag::goal;
    cPParam.positionVec = CourceDataLoader::GetCheckPointPosList();
    cPParam.directionVec = CourceDataLoader::GetCheckPointDirList();
    vecSize = cPParam.positionVec.size();
    checkPointDistance = 0;
    position = cPParam.positionVec.front();
    direction = cPParam.directionVec.front();
    radius = goalRadius;
    vecSize = cPParam.positionVec.size();
    transitCount = 0;
}
CheckPoint::~CheckPoint()
{
}

/// <summary>
/// �v���C���[���Ԃ������玟�̍s�����ݒ肷��
/// </summary>
/// <param name="carInfo">�Ԃ����������ׂ��</param>
ConflictExamineResultInfo CheckPoint::CheckPointUpdate(HitCheckExamineObjectInfo carInfo)
{  
    HitChecker checker;
    //�`�F�b�N�|�C���g�̈ʒu�ƌ������
    ConflictExamineResultInfo conflictInfo;
    conflictInfo.SetObjInfo(false, this);

    VECTOR carPos = carInfo.pos;
    carPos.y = 0;
    VECTOR pos = GetArgumentCountVector(cPParam.positionVec.begin(), transitCount % vecSize);
    VECTOR dir = GetArgumentCountVector(cPParam.directionVec.begin(), transitCount % vecSize);
    //�ʉ߂��������肷��
    if (IsTransitCheckPointCar(pos, dir, carPos))
    {
        //�`�F�b�N�|�C���g�ʉ߉񐔉��Z
        transitCount++;
        //�ʉ߂����玟�̃`�F�b�N�|�C���g�̏ꏊ���X�V
        position = GetArgumentCountVector(cPParam.positionVec.begin(), transitCount % vecSize);
        direction = GetArgumentCountVector(cPParam.directionVec.begin(), transitCount % vecSize);
        //���������GoalCount���C���N�������g
        if (transitCount >= vecSize)
        {
            goalCount++;
            transitCount = 0;
        }
        conflictInfo.pos = position;
        conflictInfo.dir = direction;
        conflictInfo.hitFlag = true;
        //�ʉ߂����珈���I��
        return conflictInfo;
    }/*
    else if (checkPointDistance < radius)
    {
        conflictInfo.pos = GetArgumentCountVector(cPParam.positionVec.begin(), (transitCount + 1) % vecSize);
        conflictInfo.dir = GetArgumentCountVector(cPParam.directionVec.begin(), (transitCount + 1) % vecSize);
        return conflictInfo;
    }*/
    return conflictInfo;
}

bool CheckPoint::IsTransitCheckPointCar(VECTOR pos, VECTOR dir, VECTOR carPos)
{
    
    VECTOR rightEdge = VAdd(VCross(dir, VGet(0, 1, 0)), pos);
    VECTOR leftEdge = VAdd(VCross(dir, VGet(0, -1, 0)), pos);
    //�E�[�ƍ��[���q���P�ʉ�
    VECTOR normLineSegment = VNorm(VSub(rightEdge,leftEdge));
    //���[����Ԃ܂ł̋���
    VECTOR leftEdgeAndCarBetween = VSub(carPos, leftEdge);
    //�`�F�b�N�|�C���g�܂ł̋������X�V
    VECTOR tempVec = VScale(normLineSegment, VDot(normLineSegment, leftEdgeAndCarBetween));
    checkPointDistance = VSize(VSub(tempVec, leftEdgeAndCarBetween));
    //�ʉ߂�����O�ς�Y��0���傫���Ȃ�B������x�ߊ���Ă���K�v������
    if (VCross(normLineSegment, leftEdgeAndCarBetween).y > 0 && checkPointDistance < radius)
    {
        return true;
    }
    return false;
}

VECTOR CheckPoint::GetLastPos()
{
    return GetArgumentCountVector(cPParam.positionVec.begin(), transitCount - 1);
}

VECTOR CheckPoint::GetLastDir()
{
    return GetArgumentCountVector(cPParam.directionVec.begin(), transitCount - 1);
}

/// <summary>
/// �S�[�������񐔂�Ԃ�
/// </summary>
/// <returns></returns>
int CheckPoint::GetGoalCount()
{
    return goalCount;
}
int CheckPoint::GetTransitCheckPointCount()
{
    return transitCount + goalCount * vecSize;
}
/// <summary>
/// �`�F�b�N�|�C���g�܂ł̋���
/// </summary>
/// <returns></returns>
float CheckPoint::GetCheckPointDistance()
{
    return checkPointDistance;
}

bool CheckPoint::HitCheckConflict(HitCheckExamineObjectInfo objInfo)
{
    objInfo.pos.y = 0;
    HitChecker checker;
    return checker.HitCheck(this,objInfo);
}