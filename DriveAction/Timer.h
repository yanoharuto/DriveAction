#pragma once

/// <summary>
/// 経過時間やデルタタイムを出すよ
/// </summary>
class Timer
{
public:
    Timer();
    Timer(float limitTime);
    ~Timer();
    void Update(float deltaTime);
    void Init();
    bool IsOverLimitTime();

private:
    float limitTime = 0;
    float elapsedTime = 0;
};

