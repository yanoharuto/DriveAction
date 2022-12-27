#include "Goal.h"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
Goal::Goal(const int roundNum)
{
    std::ifstream ifs("goalStatus.txt");
    if (!ifs)
    {
        std::cerr << "�t�@�C���I�[�v���Ɏ��s" << std::endl;
        std::exit(1);
    }
    std::string charBuf;
    if (!ifs)
    {
        std::cerr << "�ǂݍ��݂Ɏ��s" << std::endl;
        std::exit(1);
    }

    for (int i = 0; std::getline(ifs, charBuf); i++)
    {
        VECTOR goalData = {};                  //�S�[���̈ʒu�Ɠ��鎞�̕���������
        std::string backspaceChar = charBuf;   //�c��������
        int getCharNum = 0;                    //��������������
        int charLength = 0;                    //�R���}�܂ł̕�����
        while (getCharNum < 3)
        {
            charLength = backspaceChar.find(",");
            std::string chars = backspaceChar.substr(0,charLength);//�R���}�܂ł̕�����
            //�������ɉ����ăp�����[�^�[��ݒ�
            switch (getCharNum)
            {
            case 0:
                goalData.x = std::stof(chars);
                break;
            case 1:
                goalData.y = std::stof(chars);
                break;
            case 2:
                goalData.z = std::stof(chars);
                break;
            default:
                break;
            }
            backspaceChar.erase(0,charLength + 1);
            getCharNum++;
        }
        //�|�W�V����
        if (i % 2 == 0)
        {
            positionVec.push_back(goalData);
        }
        //���Ԓn�_�̕���
        else
        {
            directionVec.push_back(goalData);
        }
    }
    ifs.close();
    tag = ObjectTag::stage;
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
        if (theta > dirJugeLine)
        {
            goalNum++;
            if (goalNum / vecSize < goalRoundNum)
            {
                position = positionVec[goalNum % vecSize];
                direction = directionVec[goalNum % vecSize];
            }
            else
            {
                aliveFlag = false;
            }
        }
    }

}




