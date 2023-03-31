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
    cPParam.positionVec = GetVectorConversion(CourceDataLoader::GetVECTORData(checkPointPosPass));
    cPParam.directionVec = GetVectorConversion(CourceDataLoader::GetVECTORData(checkPointDirPass));
    vecSize = cPParam.positionVec.size();
    
}
CheckPoint::~CheckPoint()
{
}

/// <summary>
/// �v���C���[���Ԃ������玟�̍s�����ݒ肷��
/// </summary>
/// <param name="carInfo">�Ԃ����������ׂ��</param>
bool CheckPoint::IsTransitCheckPoint(int transitCount, HitCheckExamineObjectInfo carInfo)
{  
    VECTOR carPos = carInfo.pos;
    carPos.y = 0;
    VECTOR pos = cPParam.positionVec[transitCount% vecSize];
    VECTOR dir = cPParam.directionVec[transitCount% vecSize];
    //�ʉ߂��������肷��
    if (IsTransitCheckPointCar(pos, dir, carPos))
    {
        //�ʉ߂����珈���I��
        return true;
    }
    return false;
}

bool CheckPoint::IsTransitCheckPointCar(VECTOR pos, VECTOR dir, VECTOR carPos)
{
    VECTOR rightEdge = VAdd(VCross(dir, VGet(0, 1, 0)), pos);
    VECTOR leftEdge = VAdd(VCross(dir, VGet(0, -1, 0)), pos);
    //�E�[�ƍ��[���q���P�ʉ�
    VECTOR normLineSegment = VNorm(VSub(rightEdge,leftEdge));
    //���[����Ԃ܂ł̋���
    VECTOR leftEdgeAndCarBetween = VSub(carPos, leftEdge);
    //�`�F�b�N�|�C���g�܂ł̋���
    VECTOR tempVec = VScale(normLineSegment, VDot(normLineSegment, leftEdgeAndCarBetween));
    //�ʉ߂�����O�ς�Y��0���傫���Ȃ�B������x�ߊ���Ă���K�v������
    if (VCross(normLineSegment, leftEdgeAndCarBetween).y > 0)
    {
        return true;
    }
    return false;
}

/// <summary>
/// �`�F�b�N�|�C���g�܂ł̋���
/// </summary>
/// <returns></returns>
float CheckPoint::GetCheckPointDistance(int transitCount, VECTOR objPos)
{
    VECTOR dir = cPParam.directionVec[transitCount];
    VECTOR pos = cPParam.positionVec[transitCount];
    VECTOR rightEdge = VAdd(VCross(dir, VGet(0, 1, 0)), pos);
    VECTOR leftEdge = VAdd(VCross(dir, VGet(0, -1, 0)), pos);
    //�E�[�ƍ��[���q���P�ʉ�
    VECTOR normLineSegment = VNorm(VSub(rightEdge, leftEdge));
    //���[����Ԃ܂ł̋���
    VECTOR leftEdgeAndCarBetween = VSub(objPos, leftEdge);
    //�`�F�b�N�|�C���g�܂ł̋���
    VECTOR tempVec = VScale(normLineSegment, VDot(normLineSegment, leftEdgeAndCarBetween));
    return VSize(tempVec);
}

int CheckPoint::GetGoalCount(int transitCount)
{
    return transitCount / vecSize;
}

VECTOR CheckPoint::GetCheckPointPos(int transitCount)
{
    return cPParam.positionVec[transitCount%vecSize];
}

VECTOR CheckPoint::GetCheckPointDir(int transitCount)
{
    return cPParam.directionVec[transitCount%vecSize];
}
