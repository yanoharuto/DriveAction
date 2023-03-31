#pragma once

//fps
#define FLAME 60
class Clock
{
public:
    Clock();
    ~Clock();
    /// <summary>
    /// タイマーを更新する
    /// </summary>
    void Update();

    /// <summary>
    /// ゲーム開始してから何秒かかったか
    /// </summary>
    /// <returns>経過時間</returns>
    float GetScoreTime();

private:
    int startTime;
    int time;
    double timeD;
};