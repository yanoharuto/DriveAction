#include "DestinationLoader.h"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
DestinationLoader::DestinationLoader()
{
}

DestinationLoader::~DestinationLoader()
{
}

void DestinationLoader::LoadDestination(std::vector<VECTOR>* posVec, std::vector<VECTOR>* dirVec, std::string fileName)
{
    std::ifstream ifs(fileName);
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
        DxLib::VECTOR goalData = {};                  //�S�[���̈ʒu�Ɠ��鎞�̕���������
        std::string backspaceChar = charBuf;   //�c��������
        int getCharNum = 0;                    //��������������
        int charLength = 0;                    //�R���}�܂ł̕�����
        while (getCharNum < 3)
        {
            charLength = backspaceChar.find(",");
            std::string chars = backspaceChar.substr(0, charLength);//�R���}�܂ł̕�����
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
            backspaceChar.erase(0, charLength + 1);
            getCharNum++;
        }
        //�|�W�V����
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
