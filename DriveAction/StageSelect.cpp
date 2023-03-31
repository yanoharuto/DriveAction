#include "StageSelect.h"
#include "Utility.h"
static std::string fileAddres;
StageSelect::StageSelect()
{
    dataLoader = new DataPassLoader(allStageAddresFile);
    fileNameIte = dataLoader->GetBeginIterator();
    fileAddres = *fileNameIte;
    fileNameIte++;
}

StageSelect::~StageSelect()
{
    SAFE_DELETE(dataLoader);
}

void StageSelect::ChangeStage(bool up)
{
    if (up)
    {
        fileNameIte++;
        if (fileNameIte == dataLoader->GetEndIterator())
        {
            fileNameIte = dataLoader->GetBeginIterator();
        }
    }
    else
    {
        if (fileNameIte == dataLoader->GetBeginIterator())
        {
            fileNameIte = dataLoader->GetEndIterator();
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