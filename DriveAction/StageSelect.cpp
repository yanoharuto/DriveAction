#include "StageSelect.h"
#include "CircuitDataLoader.h"
StageSelect::StageSelect()
{
    class CircuitDataLoader dataLoader;
    dataLoader.GetString(&stageFileNameList,"AllStageFileName.txt");
    fileNameIte = stageFileNameList.begin();
}

StageSelect::~StageSelect()
{
}

void StageSelect::ChangeStage(bool up)
{
    fileNameIte++;
}

void StageSelect::LoadeStage()
{

}
