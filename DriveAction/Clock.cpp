#include "Clock.h"
#include "DxLib.h"
Clock::Clock()
{
    time = GetNowCount();
    deltaTime = setDeltaTime;
    startTime = GetNowCount();
    fpsCount = 0;
    averageFPS = 0;

    // 現在のカウントを取得する
    timeD = GetNowHiPerformanceCount();
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
   double temp = GetNowHiPerformanceCount() - timeD;
    while (temp < setDeltaTime)
    {
        temp = GetNowHiPerformanceCount() - timeD;
    }

    // 現在のカウントを取得する
    timeD = GetNowHiPerformanceCount();
    //int term, nowCount;
    //if (fpsCount == 0)
    //{
    //    //60フレームの1回目なら
    //    if (time == 0)//完全に最初ならまたない
    //    {
    //        term = 0;
    //    }
    //    else//前回記録した時間を元に計算
    //    {
    //        term = countZeroT + thousand - GetNowCount();
    //    }
    //}
    //else    //待つべき時間=現在あるべき時刻-現在の時刻
    //{
    //    term = (int)(countZeroT + fpsCount * (thousand / FLAME)) - GetNowCount();
    //}
    //if (term > 0)//待つべき時間だけ待つ
    //{
    //    Sleep(term);
    //}
    //nowCount = GetNowCount();

    //if (fpsCount == 0)//60フレームに1度基準を作る
    //{
    //    countZeroT = nowCount;
    //}
    //f[fpsCount] = nowCount - time;//１周した時間を記録
    //deltaTime = (nowCount - time) / thousand;
    //time = nowCount;
    ////平均計算
    //if (fpsCount == FLAME - 1) {
    //    averageFPS = 0;
    //    //合計して割る
    //    for (int i = 0; i < FLAME; i++)
    //    {
    //        averageFPS += f[i];
    //    }
    //    averageFPS /= FLAME;
    //}
    //fpsCount = (++fpsCount) % FLAME;
#ifdef _DEBUG

    //printfDx("deltaTime,%f::FPS,%d\n", deltaTime, fpsCount);

#endif
}
/// <summary>
/// デルタタイムを出すよ
/// </summary>
/// <returns></returns>
float Clock::GetDeltaTime()
{
    return deltaTime;
}

/// <summary>
/// ゲーム開始してから何秒かかったか
/// </summary>
/// <returns>経過時間</returns>
float Clock::GetScoreTime()
{
    return GetNowCount() - startTime;
}
