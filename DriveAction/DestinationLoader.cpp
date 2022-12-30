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
        std::cerr << "ファイルオープンに失敗" << std::endl;
        std::exit(1);
    }
    std::string charBuf;
    if (!ifs)
    {
        std::cerr << "読み込みに失敗" << std::endl;
        std::exit(1);
    }

    for (int i = 0; std::getline(ifs, charBuf); i++)
    {
        DxLib::VECTOR goalData = {};                  //ゴールの位置と入る時の方向が入る
        std::string backspaceChar = charBuf;   //残った文字
        int getCharNum = 0;                    //所得した文字数
        int charLength = 0;                    //コンマまでの文字数
        while (getCharNum < 3)
        {
            charLength = backspaceChar.find(",");
            std::string chars = backspaceChar.substr(0, charLength);//コンマまでの文字列
            //所得順に応じてパラメーターを設定
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
        //ポジション
        if (i % 2 == 0)
        {
            posVec->push_back(goalData);
        }
        //中間地点の方向
        else
        {
            dirVec->push_back(goalData);
        }
    }
    ifs.close();
}
