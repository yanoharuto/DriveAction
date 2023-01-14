#pragma once
class Timer;
class ScoreTime
{
public:
    ScoreTime();
    ScoreTime(Timer* timer);
    ~ScoreTime() {};
    static float GetScoreTime();
};

