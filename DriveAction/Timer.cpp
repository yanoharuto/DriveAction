#include "Timer.h"
#include "DxLib.h"
#include "Utility.h"
/// <summary>
/// 制限時間とかを計測する
/// </summary>
/// <param name="setLimitTime"></param>
Timer::Timer(float setLimitTime)
{
    limitTime = setLimitTime;
    startTime = static_cast<double>(GetNowHiPerformanceCount());
}

Timer::~Timer()
{
}
/// <summary>
/// 時間をリセット
/// </summary>
void Timer::Init()
{
    startTime = static_cast<double>(GetNowHiPerformanceCount());
}
/// <summary>
/// 設定時間を過ぎたか
/// </summary>
/// <returns>過ぎたらTrue</returns>
bool Timer::IsOverLimitTime()
{
    //経過時間
    double elaspedTime = static_cast<double>(GetNowHiPerformanceCount()) - startTime;
    return limitTime < elaspedTime / 1000000;
}
/// <summary>
/// 計測時間
/// </summary>
/// <returns></returns>
float Timer::GetLimitTime()
{
    //経過時間
    double elaspedTime = static_cast<double>(GetNowHiPerformanceCount()) - startTime;
    return limitTime - static_cast<float>(elaspedTime / 1000000);;
}
