#include "Timer.h"
#include "DxLib.h"
Timer::Timer()
{

}

Timer::Timer(float setLimitTime)
{
    limitTime = setLimitTime;
    elapsedTime = limitTime;
}

Timer::~Timer()
{
}

void Timer::Update(float deltaTime)
{
    elapsedTime -= deltaTime;
}

void Timer::Init()
{
    elapsedTime = limitTime;
}

bool Timer::IsOverLimitTime()
{
    return 0 > elapsedTime;
}
