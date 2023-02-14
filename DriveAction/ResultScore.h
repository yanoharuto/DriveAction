#pragma once
class Timer;
class ResultScore
{
public:
    ResultScore();
    ResultScore(float timer,int rank);
    ~ResultScore() {};
    static float GetScoreTime();
    static int GetPlayerRank();
};

