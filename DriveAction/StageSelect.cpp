#include "StageSelect.h"
#include "DataAddresLoader.h"
static std::string fileAddres;
StageSelect::StageSelect()
{
    DataAddressLoader dataLoader;
    dataLoader.GetString(&stageFileNameList,allStageAddresFile);
    fileNameIte = stageFileNameList.begin();
    fileAddres = *fileNameIte;
}

StageSelect::~StageSelect()
{
}

void StageSelect::ChangeStage(bool up)
{
    if (up)
    {
        fileNameIte++;
        if (fileNameIte == stageFileNameList.end())
        {
            fileNameIte = stageFileNameList.begin();
        }
    }
    else
    {
        if (fileNameIte == stageFileNameList.begin())
        {
            fileNameIte = stageFileNameList.end();
        }
        fileNameIte--;
    }
    fileAddres = *fileNameIte;
}
/// <summary>
/// どのステージを選んでいるか
/// </summary>
/// <returns>選ばれているステージのアドレスを返す</returns>
std::string StageSelect::GetLoadeStageName()
{
    return fileAddres;
}