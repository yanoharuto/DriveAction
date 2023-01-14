#include "ScoreTime.h"
#include"Timer.h"
static float scoreTime = 0.0f;
ScoreTime::ScoreTime()
{
}

ScoreTime::ScoreTime(Timer* timer)
{
    scoreTime = timer->GetScoreTime();
}

float ScoreTime::GetScoreTime()
{
    return scoreTime;
}
