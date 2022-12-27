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
        VECTOR goalData = {};                  //ゴールの位置と入る時の方向が入る
        std::string backspaceChar = charBuf;   //残った文字
        int getCharNum = 0;                    //所得した文字数
        int charLength = 0;                    //コンマまでの文字数
        while (getCharNum < 3)
        {
            charLength = backspaceChar.find(",");
            std::string chars = backspaceChar.substr(0,charLength);//コンマまでの文字列
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
            backspaceChar.erase(0,charLength + 1);
            getCharNum++;
        }
        //ポジション
        if (i % 2 == 0)
        {
            positionVec.push_back(goalData);
        }
        //中間地点の方向
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
/// プレイヤーがぶつかったら次の行き先を設定する
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




