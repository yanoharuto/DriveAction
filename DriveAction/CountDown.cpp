#include "CountDown.h"

CountDown::CountDown()
{
	countDownEnd = false;
	time = 5;
}

CountDown::~CountDown()
{
}

std::string CountDown::Update(float deltaTime)
{
	time -= deltaTime;
	if (time < 0)
	{
		time = 0;
	}
	switch (static_cast<int>(time))
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
