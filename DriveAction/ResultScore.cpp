#include "ResultScore.h"
#include <math.h>
#include <iomanip>

int ResultScore::coinScore;
int ResultScore::hitScore;
int ResultScore::timeScore;
ResultScore::ResultScore(Timer* timer, PlayerRelatedInfo playerInfo)
{
    timeScore = timer->GetLimitTime() * timeBonus;
    hitScore = noHitScore - playerInfo.damageObjHitCount * damageObjHitDec;
    coinScore = playerInfo.hitCoinCount * coinBonus;
}


int ResultScore::GetScore()
{
    return coinScore - hitScore + timeScore;
}

int ResultScore::GetCoinScore()
{
    return coinScore;
}

int ResultScore::GetHitScore()
{
    return hitScore;
}

int ResultScore::GetTimeScore()
{
    return timeScore;
}
