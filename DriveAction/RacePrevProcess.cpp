#include "RacePrevProcess.h"
#include "DxLib.h"
#include "Rule.h"
#include "SoundPlayer.h"
#include "Utility.h"
RacePrevProcess::RacePrevProcess()
{
    displaySwitchingTimer = new Timer(visibleCoolTime);
    SoundPlayer::LoadSound(fanfareSEPass);
    SoundPlayer::Play2DSE(fanfareSEPass);
    purposeData.dataHandle = LoadGraph(purposeGraph.c_str());
}

RacePrevProcess::~RacePrevProcess()
{
    DeleteGraph(purposeData.dataHandle);
}

void RacePrevProcess::Update()
{
    displaySwitchingTimer->Update();
    if (displaySwitchingTimer->IsOverLimitTime())
    {
        isVisible = !isVisible;
        displaySwitchingTimer->Init();
    }
}

void RacePrevProcess::Draw()
{
    DrawRotaGraph(purposeData.x, purposeData.y, 1,0,purposeData.dataHandle, true);
}

bool RacePrevProcess::IsProccesEnd()
{
    return !SoundPlayer::IsPlaySound(fanfareSEPass);
}
