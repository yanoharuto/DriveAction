
#include "HitNumCounter.h"
#include "ConflictManager.h"
HitNumCounter::HitNumCounter()
{
}

HitNumCounter::HitNumCounter(float setRadius)
{
    radius= setRadius;
    collider = new SphereCollider(this);
    tag = ObjectTag::countSystem;
}

HitNumCounter::~HitNumCounter()
{
    ConflictManager::EraceConflictObjInfo(collider);
}

void HitNumCounter::Update(VECTOR setPosition)
{
    position = setPosition;
}
void HitNumCounter::SetTimer(ObjectTag tag, Timer* coolTimer)
{
    collider->SetCoolTimer(tag, coolTimer);
}
/// <summary>
/// 衝突処理
/// </summary>
/// <param name="resultInfo"></param>
void HitNumCounter::ConflictProccess(ConflictExamineResultInfo resultInfo)
{
    //まだ追加したことのないタグなら追加
    if (!hitCountMap.contains(resultInfo.tag))
    {
        int hitCount = 1;
        hitCountMap.insert(std::make_pair(resultInfo.tag, hitCount));
    }
    //あるならぶつかった時に回数を増やす
    else if (resultInfo.hit == HitSituation::Enter)
    {
        hitCountMap[resultInfo.tag]++;
    }
}
 /// <summary>
 /// 引数のタグのオブジェクトに何回ぶつかったか調べる
 /// </summary>
 /// <param name="examineTag"></param>
int HitNumCounter::GetHitObjecctNum(ObjectTag examineTag)
{
    return hitCountMap[examineTag];
}
