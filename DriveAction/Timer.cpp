#include "Timer.h"
#include "DxLib.h"
Timer::Timer()
{
    time = static_cast<float>(GetNowCount());
    deltaTime = deltaTimeCalculationLine;
    startTime = time;
}

Timer::~Timer()
{
}
/// <summary>
/// タイマーを更新する
/// </summary>
void Timer::Update()
{
    while (deltaTimeCalculationLine < 0.001f)
    {
        deltaTimeCalculationLine = ((float)GetNowCount() - time) / Thousand;
    }

    while (deltaTime < deltaTimeCalculationLine)
    {
        deltaTime = ((float)GetNowCount() - time) / Thousand;
    }
#ifdef _DEBUG

    printfDx("%f,%f\n", deltaTime,deltaTimeCalculationLine);
#endif
    time = (float)GetNowCount();
}
/// <summary>
/// デルタタイムを出すよ
/// </summary>
/// <returns></returns>
float Timer::GetDeltaTime()
{
    return deltaTime;
}

/// <summary>
/// ゲーム開始してから何秒かかったか
/// </summary>
/// <returns>経過時間</returns>
float Timer::GetScoreTime()
{
    return GetNowCount() - startTime;
}
