#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
#include "SoundPlayer.h"
#define DOWN_SCALE		8				// ガウスフィルタを掛ける画像が画面のサイズの何分の１か
CountDown::CountDown(Timer* setTimer)
{
	countDownEnd = false;


	uiData.x = SCREEN_WIDTH / 2;
	uiData.y = SCREEN_HEIGHT / 2;
	oneGraph = LoadGraph(oneGraphPass.c_str());
	twoGraph = LoadGraph(twoGraphPass.c_str());
	threeGraph = LoadGraph(threeGraphPass.c_str());
	timer = setTimer;
	SoundPlayer::LoadSound(countDownSE);
}

CountDown::~CountDown()
{
	DeleteGraph(uiData.dataHandle);
}

void CountDown::Update()
{
	
	
	switch (static_cast<int>(timer->GetLimitTime()))
	{
	case 3:
		if (!countStart)
		{
			countStart = true;
			SoundPlayer::Play2DSE(countDownSE);
		}
		uiData.dataHandle = threeGraph;
	break;
	case 2:
		uiData.dataHandle = twoGraph;
		break;
	case 1:
		uiData.dataHandle = oneGraph;
		break;
	case 0:
		countDownEnd = true;
		break;
	default:
		break;
	}
}

bool CountDown::CountDownEnd()
{
	return countDownEnd;
}

void CountDown::DrawUI()
{
	DrawRotaGraph(uiData.x, uiData.y, 1, 0, uiData.dataHandle, true);
}