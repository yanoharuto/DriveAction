#include "Goal.h"
#include "DestinationLoader.h"

/// <summary>
/// �f�t�H���g�R���X�g���N�^
/// </summary>
/// <returns></returns>
Goal::Goal()
{
    direction = {};
    cPParam.goalRoundNum = 0;
    vecSize = 0;
}
/// <summary>
/// �R�[�X��񓾂����
/// </summary>
/// <param name="roundNum">���T���邩</param>
/// <param name="fileName">�ǂ̃t�@�C�����珊�����邩</param>
/// <returns></returns>
Goal::Goal(const int roundNum, const TCHAR* fileName)
{
    DestinationLoader loader;
    loader.LoadDestination(&cPParam.positionVec,&cPParam.directionVec, fileName);
    cPParam.goalRoundNum = roundNum;
    InitMember();
}
/// <summary>
/// �R�[�X��񕡐��p
/// </summary>
/// <param name="checkPointParam"></param>
/// <returns></returns>
Goal::Goal(const CircuitData circuitData)
{
    cPParam = circuitData;
    InitMember();
}

Goal::~Goal()
{
}

/// <summary>
/// �v���C���[���Ԃ������玟�̍s�����ݒ肷��
/// </summary>
/// <param name="car"></param>
void Goal::Update(Car* car)
{
    if (car->GetTag() == ObjectTag::car)
    {
        float theta = VDot(car->GetDir(), direction);
        //�Ԃ��������肪�t�����ĂȂ������玟�̃`�F�b�N�|�C���g�ɍs��
        if (theta > dirJugeLine)
        {
            goalNum++;
            //�`�F�b�N�|�C���g�ʉ߂���T���Ȃ炨�����
            if (goalNum / vecSize == cPParam.goalRoundNum)
            {
                aliveFlag = false;
            }
            else
            {
                //����ȊO�Ȃ�ʒu�X�V
                position = cPParam.positionVec[goalNum % vecSize];
                direction = cPParam.directionVec[goalNum % vecSize];
            }
        }
    }
}

/// <summary>
/// ����CPU�ɂ��R�s�[�����邽�߂ɓn��
/// </summary>
/// <returns></returns>
CircuitData Goal::GetCheckPoint() const 
{
    return cPParam;
};
/// <summary>
/// ����������
/// </summary>
void Goal::InitMember()
{
    tag = ObjectTag::goal;
    position = cPParam.positionVec.front();
    direction = cPParam.directionVec.front();
    radius = goalRadius;
    vecSize = cPParam.positionVec.size();
}




