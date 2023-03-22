#include "VECTOR3Loader.h"
#include <iostream>
#include <fstream>
#include <string>
VECTOR3Loader::VECTOR3Loader()
{
}

VECTOR3Loader::VECTOR3Loader(std::string fileName)
{
    LoadVectorData(fileName);
}

VECTOR3Loader::~VECTOR3Loader()
{
}

std::list<VECTOR>::iterator VECTOR3Loader::GetVectorListIterator()
{
    return vectorList.begin();
}

std::list<VECTOR> VECTOR3Loader::GetVectorList()
{
    return vectorList;
}

void VECTOR3Loader::LoadVectorData(std::string fileName)
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
        vectorList.push_back(goalData);
    }
    ifs.close();
}
