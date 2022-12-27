#pragma once
/// <summary>
/// 経過時間やデルタタイムを出すよ
/// </summary>
class Timer
{
public:
    Timer();
    ~Timer();
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
    const float Thousand = 1000;
    const float deltaTimeCalculationLine = 0.00001f;
    float startTime;
    float time;
    float deltaTime;
};

