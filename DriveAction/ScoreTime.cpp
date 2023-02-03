#include "ScoreTime.h"
#include"Timer.h"
static float scoreTime = 0.0f;
ScoreTime::ScoreTime()
{
}

ScoreTime::ScoreTime(float timer)
{
    scoreTime = timer;
}

float ScoreTime::GetScoreTime()
{
    return scoreTime;
}
