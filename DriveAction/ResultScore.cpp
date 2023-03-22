#include "ResultScore.h"
#include <math.h>
#include <iomanip>
static float scoreTime = 0.0f;
static int playerRank = 0.0f;
ResultScore::ResultScore()
{
}

ResultScore::ResultScore(float timer, int rank)
{
    scoreTime = round(timer * 100) / 100;
    playerRank = rank;
}

float ResultScore::GetScoreTime()
{
    return scoreTime;
}

int ResultScore::GetPlayerRank()
{
    return playerRank;
}
