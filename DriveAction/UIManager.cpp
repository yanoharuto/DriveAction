#include "UIManager.h"
#include "CSVFileLoader.h"
#include "Utility.h"
#include "DxLib.h"
std::vector<std::string> UIManager::initDataVec;
std::unordered_map<UIKind, int*> UIManager::loadGraphs;
UIManager::UIManager()
{
    CSVFileLoader* initDataFile = new CSVFileLoader(initUIDataPassFile);
    initDataVec = initDataFile->GetLoadData();
    SAFE_DELETE(initDataFile);
}

UIManager::~UIManager()
{
    for (auto itr = loadGraphs.begin(); itr != loadGraphs.end(); itr++)
    {
        DeleteGraph((*(*itr).second));
    }
}

UIData UIManager::CreateUIData(UIKind uiKind)
{
    UIData data;
    int num = static_cast<int>(uiKind) * 2 + 1;
    CSVFileLoader* initDataFile = new CSVFileLoader(initDataVec[num]);
    std::vector<std::string> dataVec = initDataFile->GetLoadData();
    data.x = atoi(dataVec[1].c_str());
    data.y = atoi(dataVec[3].c_str());
    int xNum = atoi(dataVec[9].c_str());
    int yNum =  atoi(dataVec[11].c_str());
    data.width = atoi(dataVec[5].c_str()) / xNum;
    data.height = atoi(dataVec[7].c_str()) / yNum;
    data.graphNum = xNum + yNum - 1;
    int graphArray[1000];
    LoadDivGraph(dataVec[13].c_str(), data.graphNum, xNum, yNum, data.width, data.height, graphArray);
    for (int i = 0; i < xNum + yNum - 1; i++)
    {
        data.dataHandle.push_back(graphArray[i]);
    }
    data.size = atof(dataVec[15].c_str());
    loadGraphs.insert(std::make_pair(uiKind, graphArray));
    return data;
}


