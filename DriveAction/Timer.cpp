#include "Timer.h"
#include "DxLib.h"
Timer::Timer()
{
    time = 0;
    deltaTime = deltaTimeCalculationLine;
    startTime = GetNowCount();
    fpsCount = 0;
    averageFPS = 0;
}

Timer::~Timer()
{
}
/// <summary>
/// タイマーを更新する
/// </summary>
void Timer::Update()
{
    int term, nowCount;

    if (fpsCount == 0) 
    {
        //60フレームの1回目なら
        if (time == 0)//完全に最初ならまたない
        {
            term = 0;
        }
        else//前回記録した時間を元に計算
        {
            term = countZeroT + thousand - GetNowCount();
        }
    }
    else    //待つべき時間=現在あるべき時刻-現在の時刻
    {
        term = (int)(countZeroT + fpsCount * (thousand / FLAME)) - GetNowCount();
    }

    if (term > 0)//待つべき時間だけ待つ
    {
        Sleep(term);
    }
    nowCount = GetNowCount();

    if (fpsCount == 0)//60フレームに1度基準を作る
    {
        countZeroT = nowCount;
    }
    f[fpsCount] = nowCount - time;//１周した時間を記録
    deltaTime = (nowCount - time) / thousand;
    time = nowCount;
    //平均計算
    if (fpsCount == FLAME - 1) {
        averageFPS = 0;
        //合計して割る
        for (int i = 0; i < FLAME; i++)
        {
            averageFPS += f[i];
        }
        averageFPS /= FLAME;
    }
    fpsCount = (++fpsCount) % FLAME;

    
#ifdef _DEBUG

   // printfDx("deltaTime,%f::FPS,%d\n", deltaTime, fpsCount);

#endif
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
