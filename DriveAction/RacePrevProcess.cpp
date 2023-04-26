#include "RacePrevProcess.h"
#include "DxLib.h"
#include "Rule.h"
#include "SoundPlayer.h"
#include "Utility.h"
RacePrevProcess::RacePrevProcess()
{
    SoundPlayer::LoadSound(fanfareSEPass);
    SoundPlayer::Play2DSE(fanfareSEPass);
    gamePuroseData = UIManager::CreateUIData(gamePurose);
    collectIconData = UIManager::CreateUIData(collectIcon);
}

RacePrevProcess::~RacePrevProcess()
{
}

void RacePrevProcess::Update()
{

}

void RacePrevProcess::Draw()
{
    DrawRotaGraph(gamePuroseData.x, gamePuroseData.y, 1,0,gamePuroseData.dataHandle[0], true);
}

bool RacePrevProcess::IsProccesEnd()
{
    return !SoundPlayer::IsPlaySound(fanfareSEPass);
}
