#include "StageSelect.h"
#include "Utility.h"
#include "ListUtility.h"
static std::string fileAddres;
StageSelect::StageSelect()
{
    dataLoader = LoadData(allStageAddresFile);
    fileNameIte = dataLoader.begin();
    fileAddres = *fileNameIte;
    fileNameIte++;
}

StageSelect::~StageSelect()
{
}

void StageSelect::ChangeStage(bool up)
{
    if (up)
    {
        fileNameIte++;
        if (fileNameIte == dataLoader.end())
        {
            fileNameIte = dataLoader.begin();
        }
    }
    else
    {
        if (fileNameIte == dataLoader.begin())
        {
            fileNameIte = dataLoader.end();
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