#pragma once
#include <unordered_map>
#include "SphereCollider.h"
#include "Actor.h"
#include "Timer.h"
class HitNumCounter :public Actor
{
public:
    HitNumCounter();
    HitNumCounter(float setRadius);

    /// <summary>
    /// 
    /// </summary>
    ~HitNumCounter()override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="setPosition"></param>
    void Update(VECTOR setPosition);
    void SetTimer(ObjectTag tag,Timer* coolTimer);
    /// <summary>
    /// �Փˏ���
    /// </summary>
    /// <param name="resultInfo"></param>
    void ConflictProccess(ConflictExamineResultInfo resultInfo)override;
    /// <summary>
    /// �����̃^�O�̃I�u�W�F�N�g�ɉ���Ԃ����������ׂ�
    /// </summary>
    /// <param name="examineTag"></param>
    /// <returns></returns>
    int GetHitObjecctNum(ObjectTag examineTag);
private:
    SphereCollider* collider;
    std::unordered_map<ObjectTag, int> hitCountMap;
};

