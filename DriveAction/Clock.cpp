#include "Clock.h"
#include "DxLib.h"
#include "Utility.h"

Clock::Clock()
{
    time = GetNowCount();
    startTime = GetNowCount();

    // 現在のカウントを取得する
    timeD = static_cast<double>(GetNowHiPerformanceCount());
}

Clock::~Clock()
{
}

/// <summary>
/// タイマーを更新する
/// </summary>
void Clock::Update()
{
    // １７ミリ秒(約秒間６０フレームだった時の１フレームあたりの経過時間)
    // 経過するまでここで待つ
   double temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
    while (temp < DELTATIME)
    {
        temp =  static_cast<double>(GetNowHiPerformanceCount()) - timeD;
    }

    // 現在のカウントを取得する
    timeD =  static_cast<double>(GetNowHiPerformanceCount());
}

/// <summary>
/// ゲーム開始してから何秒かかったか
/// </summary>
/// <returns>経過時間</returns>
float Clock::GetScoreTime()
{
    return static_cast<int>(GetNowCount() - startTime);
}
