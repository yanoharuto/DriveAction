#include "RacePrevProcess.h"
#include "DxLib.h"
#include "SoundPlayer.h"
#include "Utility.h"
#include "Timer.h"
RacePrevProcess::RacePrevProcess()
{
    SoundPlayer::LoadSound(fanfareSEPass);
    SoundPlayer::Play2DSE(fanfareSEPass);
    gamePuroseData = UIManager::CreateUIData(gamePurose);
    frameByFrameTimer = new Timer(gamePuroseData.frameSpeed);
}

RacePrevProcess::~RacePrevProcess()
{
}

void RacePrevProcess::Update()
{
    if (frameByFrameTimer->IsOverLimitTime())
    {
        frameByFrameTimer->Init();
        iconIncrement++;
    }
}

void RacePrevProcess::Draw()
{
    int num = iconIncrement % gamePuroseData.dataHandle.size();
    DrawRotaGraph(gamePuroseData.x, gamePuroseData.y, 1,0,gamePuroseData.dataHandle[num], true);
}

bool RacePrevProcess::IsProccesEnd()
{
    return !SoundPlayer::IsPlaySound(fanfareSEPass);
}
