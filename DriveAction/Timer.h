#pragma once

/// <summary>
/// 決められた時間進んだりする
/// </summary>
class Timer
{
public:
    Timer();
    Timer(float limitTime);
    ~Timer();
    //デルタタイム分減算
    void Update();
    void Init();
    bool IsOverLimitTime();
    float GetLimitTime();
private:
    float limitTime = 0;
    float elapsedTime = 0;
};

