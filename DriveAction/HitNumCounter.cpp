
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
/// �Փˏ���
/// </summary>
/// <param name="resultInfo"></param>
void HitNumCounter::ConflictProccess(ConflictExamineResultInfo resultInfo)
{
    //�܂��ǉ��������Ƃ̂Ȃ��^�O�Ȃ�ǉ�
    if (!hitCountMap.contains(resultInfo.tag))
    {
        int hitCount = 1;
        hitCountMap.insert(std::make_pair(resultInfo.tag, hitCount));
    }
    //����Ȃ�Ԃ��������ɉ񐔂𑝂₷
    else if (resultInfo.hit == HitSituation::Enter)
    {
        hitCountMap[resultInfo.tag]++;
    }
}
 /// <summary>
 /// �����̃^�O�̃I�u�W�F�N�g�ɉ���Ԃ����������ׂ�
 /// </summary>
 /// <param name="examineTag"></param>
int HitNumCounter::GetHitObjecctNum(ObjectTag examineTag)
{
    return hitCountMap[examineTag];
}
