#include "ResultScore.h"
#include <math.h>
#include <iomanip>
#include "Timer.h"
#include "PlayerRelatedInfo.h"
//収集物のスコア
int ResultScore::collectScore;
//敵にヒットすると減点するスコア
int ResultScore::hitScore;
//残り時間ボーナス
int ResultScore::timeScore;
ResultScore::ResultScore(Timer* timer, PlayerRelatedInfo playerInfo)
{
    timeScore = timer->GetLimitTime() * timeBonus;
    hitScore = noHitScore - playerInfo.damageObjHitCount * damageObjHitDec;
    collectScore = playerInfo.hitCoinCount * coinBonus;
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
        return collectScore;
        break;
    case ScoreKind::total:
        return timeScore + hitScore + collectScore;
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
        return collectScore;
        break;
    case ScoreKind::total:
        return timeScore + hitScore + collectScore;
        break;
    default:
        break;
    }
    return 0;
}

int ResultScore::GetCollectBonus()
{
    return coinBonus;
}

int ResultScore::GetHitDecrease()
{
    return damageObjHitDec;
}

int ResultScore::GetTimeBunus()
{
    return timeScore;
}
