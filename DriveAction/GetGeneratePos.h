#pragma once
#include <vector>
#include <string>
#include "DxLib.h"
#include "CSVFileLoader.h"
#include "Utility.h"

class GetGeneratePos
{

public:
    GetGeneratePos() {};
    ~GetGeneratePos() {};
    static std::vector<VECTOR> CSVConvertPosition(std::string fileName,int dataNum)
    {
        CSVFileLoader* csv = new CSVFileLoader(fileName.c_str());
        std::vector<std::string> rockList;
        rockList = csv->GetLoadData();
        int lineCount = csv->GetLineCount();
        SAFE_DELETE(csv);
        std::vector<VECTOR> posList;
        int sideLine = rockList.size() / lineCount;
        for (int i = 0; i < lineCount; i++)
        {
            for (int j = 0; j < sideLine; j++)
            {
                int num = i * lineCount + j;
                if (std::atof(rockList[num].c_str()) == dataNum)
                {
                    VECTOR pos;
                    pos.x = j * 12000 / lineCount - 6000;
                    pos.z = i * 12000 / sideLine - 6000;
                    posList.push_back(pos);
                }
            }
        }
        return posList;
    }
};