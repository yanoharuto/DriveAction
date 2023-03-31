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
/// �ǂ̃X�e�[�W��I��ł��邩
/// </summary>
/// <returns>�I�΂�Ă���X�e�[�W�̃A�h���X��Ԃ�</returns>
std::string StageSelect::GetLoadeStageName()
{
    return fileAddres;
}