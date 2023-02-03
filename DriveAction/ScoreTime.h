#pragma once
class Timer;
class ScoreTime
{
public:
    ScoreTime();
    ScoreTime(float timer);
    ~ScoreTime() {};
    static float GetScoreTime();
};

