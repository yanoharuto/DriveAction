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
/// �ǂ̃X�e�[�W��I��ł��邩
/// </summary>
/// <returns>�I�΂�Ă���X�e�[�W�̃A�h���X��Ԃ�</returns>
std::string StageSelect::GetLoadeStageName()
{
    return fileAddres;
}