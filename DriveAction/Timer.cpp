#include "Timer.h"
#include "DxLib.h"
#include "Utility.h"
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

void Timer::Update()
{
    elapsedTime -= DELTATIME;
}

void Timer::Init()
{
    elapsedTime = limitTime;
}

bool Timer::IsOverLimitTime()
{
    return 0 > elapsedTime;
}

float Timer::GetLimitTime()
{
    return elapsedTime;
}
