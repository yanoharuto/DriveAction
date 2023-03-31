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
    /// 更新
    /// </summary>
    /// <param name="setPosition"></param>
    void Update(VECTOR setPosition);
    void SetTimer(ObjectTag tag,Timer* coolTimer);
    /// <summary>
    /// 衝突処理
    /// </summary>
    /// <param name="resultInfo"></param>
    void ConflictProccess(ConflictExamineResultInfo resultInfo)override;
    /// <summary>
    /// 引数のタグのオブジェクトに何回ぶつかったか調べる
    /// </summary>
    /// <param name="examineTag"></param>
    /// <returns></returns>
    int GetHitObjecctNum(ObjectTag examineTag);
private:
    SphereCollider* collider;
    std::unordered_map<ObjectTag, int> hitCountMap;
};

