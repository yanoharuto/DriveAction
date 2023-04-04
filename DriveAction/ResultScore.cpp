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

int ResultScore::GetScore(ScoreKind scoreKind)
{
    switch (scoreKind)
    {
    case ScoreKind::time:
        return timeScore;
         break;
    case ScoreKind::hit:
        return hitScore;
        break;
    case ScoreKind::collect:
        return coinScore;
        break;
    case ScoreKind::total:
        return timeScore + hitScore + coinScore;
        break;
    default:
        break;
    }
    return 0;
}

int ResultScore::GetScore(int kindNum)
{
    switch (kindNum)
    {
    case ScoreKind::time:
        return timeScore;
        break;
    case ScoreKind::hit:
        return hitScore;
        break;
    case ScoreKind::collect:
        return coinScore;
        break;
    case ScoreKind::total:
        return timeScore + hitScore + coinScore;
        break;
    default:
        break;
    }
    return 0;
}

int ResultScore::GetCollectBonus()
{
    return 0;
}

int ResultScore::GetHitBunus()
{
    return 0;
}

int ResultScore::GetTimeBunus()
{
    return 0;
}
