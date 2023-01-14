#include "ScoreTime.h"
#include"Timer.h"
static float scoreTime = 0.0f;
ScoreTime::ScoreTime()
{
}

ScoreTime::ScoreTime(Timer* timer)
{
    scoreTime = timer->GetScoreTime();
    scoreTime /= 1000;
}

float ScoreTime::GetScoreTime()
{
    return scoreTime;
}
