#include "DestinationLoader.h"
#include <iostream>
#include <fstream>
#include <string>
DestinationLoader::DestinationLoader()
{
}

DestinationLoader::~DestinationLoader()
{
}

void DestinationLoader::LoadCheckPoint(std::vector<VECTOR>* posVec, std::vector<VECTOR>* dirVec, std::string fileName)
{
    std::ifstream ifs(fileName);
    if (!ifs)
    {
        std::cerr << "�ǂݍ��݂Ɏ��s" << std::endl;
        std::exit(1);
    }
    std::string charBuf;
    //�s�̐������`�F�b�N�|�C���g������
    for (int i = 0; std::getline(ifs, charBuf); i++)
    {
        DxLib::VECTOR goalData = {};                  //�S�[���̈ʒu�Ɠ��鎞�̕���������
        std::string backspaceChar = charBuf;          //�c��������
        int lineProcessNum = 0;                       //���̍s�ōs���������̉�
        int charLength = 0;                           //�R���}�܂ł̕�����
        //3�񏈗����s������GoalData�̊���
        while (lineProcessNum < 3)
        {
            charLength = backspaceChar.find(",");
            std::string chars = backspaceChar.substr(0, charLength);//�R���}�܂ł̕�����
            //�������ɉ����ăp�����[�^�[��ݒ�
            switch (lineProcessNum)
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
            //�ݒ肵��������͏���
            backspaceChar.erase(0, charLength + 1);
            lineProcessNum++;
        }
        //�|�W�V�����̐ݒ�
        if (i % 2 == 0)
        {
            posVec->push_back(goalData);
        }
        //���Ԓn�_�̕���
        else
        {
            dirVec->push_back(goalData);
        }
    }
    ifs.close();
}
