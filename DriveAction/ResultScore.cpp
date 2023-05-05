#include <iostream>
#include <fstream>
#include <math.h>
#include "ResultScore.h"
#include "Timer.h"
#include "ObjectObserver.h"
#include "RacerManager.h"
#include "SubjectInfoCentor.h"
#include "Object.h"
//収集物のスコア
int ResultScore::collectScore;
//敵にヒットすると減点するスコア
int ResultScore::hitScore;
//残り時間ボーナス
int ResultScore::timeScore;

ResultScore::ResultScore(Timer* timer,RacerManager* racerManager)
{
    timeScore = static_cast<int>(timer->GetLimitTime() * timeBonus);
    playerObserver = SubjectInfoCentor::GetObjectObserver(racerManager->GetPlayerSubject(0));

    hitScore = noHitScore - playerObserver->GetObjHitCount(Object::ObjectTag::damageObject) * damageObjHitDec;
    collectScore = playerObserver->GetObjHitCount(Object::ObjectTag::coin) * coinBonus;
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
