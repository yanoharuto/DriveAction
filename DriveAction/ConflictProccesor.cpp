#include "conflictProccesor.h"
#include "HitChecker.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
ConflictProccesor::ConflictProccesor(Actor* obj)
{
    object = obj;
    ConflictManager::AddConflictObjInfo(this);
}

ConflictProccesor::~ConflictProccesor()
{

}
/// <summary>
/// 当たり判定で必要な情報を渡す
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo ConflictProccesor::GetHitExamineCheckInfo()
{
    HitCheckExamineObjectInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
/// <summary>
/// 当たり判定の処理を呼び出す
/// </summary>
/// <param name="resultInfo"></param>
void ConflictProccesor::ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo)
{
    for (auto ite = resultInfo.begin(); ite != resultInfo.end(); ite++)
    {
        if ((*ite).hit != HitSituation::NotHit)
        {
            if (coolTimer.contains((*ite).tag))
            {
                //クールタイムが過ぎていて当たっているなら
                if (coolTimer[(*ite).tag]->IsOverLimitTime())
                {
                    //当たった時の処理を行う
                    object->ConflictProccess((*ite));
                }
            }
            else
            {
                //当たった時の処理を行う
                object->ConflictProccess((*ite));
            }
        }
    }
}
/// <summary>
/// 当たり判定で特定のものにクールタイムが発生する場合タイマーをセット出来る
/// </summary>
/// <param name="tag">特定の者のタグ</param>
/// <param name="timer">クールタイム計測用のタイマー</param>
void ConflictProccesor::SetCoolTimer(ObjectTag tag,Timer* timer)
{
    coolTimer.insert(std::make_pair(tag, timer));
}
