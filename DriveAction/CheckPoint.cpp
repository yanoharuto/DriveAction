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
bool CheckPoint::CheckPointUpdate(ConflictExamineResultInfo carInfo)
{  
    HitChecker checker;
    ConflictExamineResultInfo thisInfo = {};//���̃`�F�b�N�|�C���g�N���X�̏��
    thisInfo.radius = radius;
    //���񂩂����`�F�b�N�|�C���g��ʉ߂��������ׂ�
    for (int i = 0; i < vectorExamineCount; i++)
    {
        int count = (transitCheckPointCount + i) % vecSize;
        count = count > vecSize ? vecSize : count;
        thisInfo.pos = GetArgumentCountVector(cPParam.positionVec.begin(), count);
        if (checker.HitCheck(carInfo, thisInfo))
        {
            VECTOR startPos = VAdd(VScale(VCross(direction, VGet(0, 1, 0)), radius), position);
            VECTOR endPos = VAdd(VScale(VCross(direction, VGet(0, -1, 0)), radius), position);
            VECTOR dir = VSub(endPos, startPos);
            VECTOR dir2 = VSub(carInfo.pos, startPos);
            float crossY = VCross(VNorm(dir), VNorm(dir2)).y;
            if (crossY > 0)
            {
                transitCheckPointCount += i + 1;
                //1�T�����Ȃ�
                if (transitCheckPointCount >= vecSize)
                {
                    goalCount++;
                    transitCheckPointCount = 0;
                }
                position = GetArgumentCountVector(cPParam.positionVec.begin(), transitCheckPointCount % vecSize);
                direction = GetArgumentCountVector(cPParam.directionVec.begin(), transitCheckPointCount % vecSize);

                return true;
            }
        }
    }
    //�Ō�ɖڕW�n�_�܂łǂ̂��炢����Ă邩
    checkPointDistance = VSize(VSub(position,carInfo.pos));
    return false;
}

/// <summary>
/// ����CPU�ɂ��R�s�[�����邽�߂ɓn��
/// </summary>
/// <returns></returns>
CircuitData CheckPoint::GetCheckPoint() const 
{
    return cPParam;
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




