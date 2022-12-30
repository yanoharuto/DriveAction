#include "Goal.h"
#include "DestinationLoader.h"

Goal::Goal()
{
    direction = {};
    goalRoundNum = 0;
    vecSize = 0;
}

Goal::Goal(const int roundNum, const TCHAR* fileName)
{
    DestinationLoader loader;
    loader.LoadDestination(&positionVec,&directionVec, fileName);
    tag = ObjectTag::goal;
    goalRoundNum = roundNum;
    position = positionVec.front();
    direction = directionVec.front();
    radius = goalRadius;
    vecSize = positionVec.size();
}

Goal::~Goal()
{
}

/// <summary>
/// �v���C���[���Ԃ������玟�̍s�����ݒ肷��
/// </summary>
/// <param name="actor"></param>
void Goal::ConflictProcess(Actor* actor)
{
    if (actor->GetTag() == ObjectTag::player)
    {
        float theta = VDot(actor->GetDir(), direction);
        //�Ԃ��������肪�t�����ĂȂ������玟�̃`�F�b�N�|�C���g�ɍs��
        if (theta > dirJugeLine)
        {
            goalNum++;
            //�`�F�b�N�|�C���g�ʉ߂���T���Ȃ炨�����
            if (goalNum / vecSize == goalRoundNum)
            {
                aliveFlag = false;
            }
            else
            {
                //����ȊO�Ȃ�ʒu�X�V
                position = positionVec[goalNum % vecSize];
                direction = directionVec[goalNum % vecSize];
            }
        }
    }
}




