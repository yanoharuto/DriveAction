#include "ResultScore.h"
#include"Timer.h"
static float scoreTime = 0.0f;
static int playerRank = 0.0f;
ResultScore::ResultScore()
{
}

ResultScore::ResultScore(float timer, int rank)
{
    scoreTime = timer;
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
