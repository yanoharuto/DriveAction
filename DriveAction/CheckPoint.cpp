#include "CheckPoint.h"
#include "VECTOR3Loader.h"
#include "HitChecker.h"
#include "Utility.h"
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
    InitMember();
}

CheckPoint::~CheckPoint()
{
}

/// <summary>
/// �v���C���[���Ԃ������玟�̍s�����ݒ肷��
/// </summary>
/// <param name="carInfo">�Ԃ����������ׂ��</param>
bool CheckPoint::CheckPointUpdate(ArgumentConflictInfo carInfo)
{  
    HitChecker checker;
    for (int i = 0; i < vectorExamineCount; i++)
    {
        //�Ԃ��x�N�^�[�̒n�_��ʉ߂��ĂȂ������ׂ�
        if (checker.HitCheck(this, carInfo))
        {
            float theta = VDot(carInfo.dir, direction);
            //�Ԃ��������肪�t�����ĂȂ������玟�̃`�F�b�N�|�C���g�ɍs��
            if (theta > dirJugeLine)
            {
                transitCheckPointCount += i + 1;
                //�S�[������ɍs������ŏ��̃`�F�b�N�|�C���g�����
                if (transitCheckPointCount >= static_cast<int>(cPParam.positionVec.size()))
                {
                    transitCheckPointCount = 0;
                }
                position = GetVector(cPParam.positionVec.begin(),transitCheckPointCount);
                direction = GetVector(cPParam.directionVec.begin(), transitCheckPointCount);
            }
            return true;
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
int CheckPoint::GetTransitCheckPointCout()
{
    return transitCheckPointCount;
}
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




