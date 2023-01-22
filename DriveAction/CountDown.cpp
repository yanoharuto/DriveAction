#include "CountDown.h"
#include "DxLib.h"
#include "Utility.h"
CountDown::CountDown()
{
	countDownEnd = false;
	startTime = fiveTime;
	UIData uiData;
	uiData.x = SCREEN_WIDTH / 2;
	uiData.y = SCREEN_HEIGHT / 7;
	uiData.dataHandle = CreateFontToHandle("BIZ UDÉSÉVÉbÉN", 64, 3, DX_FONTTYPE_NORMAL);
	countDownUI = new StringUI(GetColor(230, 0, 0), uiData);
}

CountDown::~CountDown()
{
	SAFE_DELETE(countDownUI);
}

void CountDown::Update(float deltaTime)
{
	startTime -= deltaTime;
	switch (static_cast<int>(startTime))
	{
	case 3:
		count = "3";
		break;
	case 2:
		count = "2";
		break;
	case 1:
		count = "1";
		break;
	case 0:
		countDownEnd = true;
		count = "GO!!";
		break;
	default:
		count = "Count...";
		break;
	}
	countDownUI->UpdateString(count);
}

bool CountDown::CountDownEnd()
{
	return countDownEnd;
}

void CountDown::DrawUI()
{
	countDownUI->DrawUI();
}
