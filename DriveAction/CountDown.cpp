#include "CountDown.h"
#include "DxLib.h"
CountDown::CountDown()
{
	countDownEnd = false;
	startTime = 5.0f;
}

CountDown::~CountDown()
{
}

std::string CountDown::Update(float deltaTime)
{
	startTime -= deltaTime;
	switch (static_cast<int>(startTime))
	{
	case 3:
		return "3";
	case 2:
		return "2";
	case 1:
		return "1";
	case 0:
		countDownEnd = true;
		return "GO!!";
	default:
		return "Count...";
	}
}

bool CountDown::CountDownEnd()
{
	return countDownEnd;
}
