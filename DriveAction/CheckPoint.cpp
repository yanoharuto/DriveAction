#include "CheckPoint.h"
#include "VECTOR3Loader.h"
#include "HitChecker.h"
#include "Utility.h"
#include "ListUtility.h"
#include "OriginalMath.h"
/// <summary>
/// �f�t�H���g�R���X�g���N�^
/// </summary>
/// <returns></returns>
CheckPoint::CheckPoint()
{
    direction = {};
    vecSize = 0;
}

/// <summary>
/// �R�[�X��񕡐��p
/// </summary>
/// <param name="checkPointParam"></param>
/// <returns></returns>
CheckPoint::CheckPoint(const CircuitData circuitData)
{
    cPParam = circuitData;
    vecSize = circuitData.positionVec.size();
    checkPointDistance = 0;
    tag = ObjectTag::goal;
    position = cPParam.positionVec.front();
    direction = cPParam.directionVec.front();
    radius = goalRadius;
    vecSize = cPParam.positionVec.size();
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
    ConflictExamineResultInfo conflictInfo;
    conflictInfo.SetObjInfo(false, this);
    VECTOR carPos = carInfo.pos;
    carPos.y = 0;
    //���񂩂����`�F�b�N�|�C���g��ʉ߂��������ׂ�
    for (int i = 0; i < checkPointExamineCount; i++)
    {
        int count = (transitCheckPointCount + i) % vecSize;//����̂����̒ʉ߉�
        count = count > vecSize ? vecSize : count;
        VECTOR pos = GetArgumentCountVector(cPParam.positionVec.begin(), count);
        VECTOR dir = GetArgumentCountVector(cPParam.directionVec.begin(), count);
        //�ʉ߂��������肷��
        if (IsTransitCheckPointCar(pos, dir, carPos))
        {
            //�`�F�b�N�|�C���g�ʉ߉񐔉��Z
            transitCheckPointCount += i + 1;
            position = GetArgumentCountVector(cPParam.positionVec.begin(), transitCheckPointCount % vecSize);
            direction = GetArgumentCountVector(cPParam.directionVec.begin(), transitCheckPointCount % vecSize);
            if (transitCheckPointCount >= vecSize)
            {
                goalCount++;
                transitCheckPointCount = 0;
            }
            conflictInfo.pos = position;
            conflictInfo.dir = direction;
            conflictInfo.hitFlag = true;
            return conflictInfo;
        }
        else if (checkPointDistance < radius)
        {
            conflictInfo.pos = GetArgumentCountVector(cPParam.positionVec.begin(),( transitCheckPointCount+1) % vecSize);
            conflictInfo.dir = GetArgumentCountVector(cPParam.directionVec.begin(), (transitCheckPointCount + 1) % vecSize);
            conflictInfo.hitFlag = true;
            return conflictInfo;
        }
    }

    return conflictInfo;
}

bool CheckPoint::IsTransitCheckPointCar(VECTOR pos, VECTOR dir, VECTOR carPos)
{
    
    VECTOR rightEdge = VAdd(VScale(VCross(dir, VGet(0, 1, 0)), goalTapeHalfLength), pos);
    VECTOR leftEdge = VAdd(VScale(VCross(dir, VGet(0, -1, 0)), goalTapeHalfLength), pos);
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
    return GetArgumentCountVector(cPParam.positionVec.begin(), transitCheckPointCount - 1);
}

VECTOR CheckPoint::GetLastDir()
{
    return GetArgumentCountVector(cPParam.directionVec.begin(), transitCheckPointCount - 1);
}

VECTOR CheckPoint::GetNextCheckLineNorm()
{
    VECTOR rightEdge = VAdd(VScale(VCross(direction, VGet(0, 1, 0)), goalTapeHalfLength), position);
    VECTOR leftEdge = VAdd(VScale(VCross(direction, VGet(0, -1, 0)), goalTapeHalfLength), position);
    return VNorm(VSub(rightEdge, leftEdge));
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
    return transitCheckPointCount + goalCount * vecSize;
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



