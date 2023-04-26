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
/// �ǂ̃X�e�[�W��I��ł��邩
/// </summary>
/// <returns>�I�΂�Ă���X�e�[�W�̃A�h���X��Ԃ�</returns>
std::string StageSelect::GetLoadeStageName()
{
    return fileAddres;
}