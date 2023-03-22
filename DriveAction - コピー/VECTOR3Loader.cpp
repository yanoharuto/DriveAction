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
        std::cerr << "読み込みに失敗" << std::endl;
        std::exit(1);
    }
    std::string charBuf;
    //行の数だけチェックポイントがある
    for (int i = 0; std::getline(ifs, charBuf); i++)
    {
        DxLib::VECTOR goalData = {};                  //ゴールの位置と入る時の方向が入る
        std::string backspaceChar = charBuf;          //残った文字
        int lineProcessNum = 0;                       //この行で行った処理の回数
        int charLength = 0;                           //コンマまでの文字数
        //3回処理を行ったらGoalDataの完成
        while (lineProcessNum < 3)
        {
            charLength = backspaceChar.find(",");
            std::string chars = backspaceChar.substr(0, charLength);//コンマまでの文字列
            //所得順に応じてパラメーターを設定
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
            //設定した文字列は消す
            backspaceChar.erase(0, charLength + 1);
            lineProcessNum++;
        }
        vectorList.push_back(goalData);
    }
    ifs.close();
}
