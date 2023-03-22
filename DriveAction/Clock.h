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
    /// デルタタイムを出すよ
    /// </summary>
    /// <returns></returns>
    float GetDeltaTime();
    /// <summary>
    /// ゲーム開始してから何秒かかったか
    /// </summary>
    /// <returns>経過時間</returns>
    float GetScoreTime();

private:
    int FPS = 0;
    int FPSCounter = 0;
    float FPSCheckTime = 0;
    const float thousand = 1000;
    const float setDeltaTime = 0.016667f;
    int startTime;
    int time;
    float deltaTime;
    double timeD;
    //fpsのカウンタ、60フレームに1回基準となる時刻を記録する変数
    int fpsCount, countZeroT;
    //平均を計算するため60回の1周時間を記録
    int f[FLAME];
    //平均fps
    double averageFPS;
};