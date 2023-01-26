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
    InitMember();
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
    HitCheckExamineObjectInfo thisInfo = {};//���̃`�F�b�N�|�C���g�N���X�̏��
    ConflictExamineResultInfo conflictInfo;
    conflictInfo.SetObjInfo(false, this);
    thisInfo.radius = radius;
    //���񂩂����`�F�b�N�|�C���g��ʉ߂��������ׂ�
    for (int i = 0; i < vectorExamineCount; i++)
    {
        int count = (transitCheckPointCount + i) % vecSize;
        count = count > vecSize ? vecSize : count;
        thisInfo.pos = GetArgumentCountVector(cPParam.positionVec.begin(), count);
        if (checker.HitCheck(carInfo, thisInfo))
        {
            //startPos����endPos�܂ł̊Ԃ�ʉߏ���
            VECTOR startPos = VAdd(VScale(VCross(direction, VGet(0, 1, 0)), radius), position);
            VECTOR endPos = VAdd(VScale(VCross(direction, VGet(0, -1, 0)), radius), position);
            //startPos��endPos�̈ʒu�̋���
            VECTOR dir = VSub(endPos, startPos);
            //�Ԃ�startPos�̈ʒu����ǂꂾ������Ă��邩�o��
            VECTOR dir2 = VSub(carInfo.pos, startPos);
            float crossY = VCross(VNorm(dir), VNorm(dir2)).y;
            //�ʉ߂����Ƃ��͊O�ς�Y���v���X�ɂȂ�
            if (crossY > 0)
            {
                //�`�F�b�N�|�C���g�ʉ߉񐔉��Z
                transitCheckPointCount += i + 1;

                position = GetArgumentCountVector(cPParam.positionVec.begin(), transitCheckPointCount % vecSize);
                direction = GetArgumentCountVector(cPParam.directionVec.begin(), transitCheckPointCount % vecSize);
                conflictInfo.pos = position;
                conflictInfo.dir = direction;
                conflictInfo.hitFlag = true;
                //1�T�����Ȃ�
                if (transitCheckPointCount >= vecSize)
                {
                    goalCount++;
                    transitCheckPointCount = 0;
                }
                return conflictInfo;
            }
        }
    }
    //�Ō�ɖڕW�n�_�܂łǂ̂��炢����Ă邩
    checkPointDistance = VSize(VSub(position,carInfo.pos));
    return conflictInfo;
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
;
/// <summary>
/// ����������
/// </summary>
void CheckPoint::InitMember()
{
    tag = ObjectTag::goal;
    position = cPParam.positionVec.front();
    direction = cPParam.directionVec.front();
    radius = goalRadius;
    vecSize = cPParam.positionVec.size();
}




