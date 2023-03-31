#include "ConflictManager.h"

std::list<ConflictProccesor*> ConflictManager::conflictObjList;
std::unordered_map<ConflictProccesor*, std::list<ConflictProccesor*>> ConflictManager::conflictMap;
ConflictManager::ConflictManager()
{
}

ConflictManager::~ConflictManager()
{

}
/// <summary>
/// 当たり判定を追加
/// </summary>
/// <param name="conflictProccesor"></param>
void ConflictManager::AddConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    conflictObjList.push_back(conflictProccesor);
}
/// <summary>
///　当たり判定をしなくていいようにする
/// </summary>
/// <param name="conflictProccesor"></param>
void ConflictManager::EraceConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    conflictMap.erase(conflictProccesor);
    auto procceesor = std::find(conflictObjList.begin(), conflictObjList.end(), conflictProccesor);
    if (procceesor != conflictObjList.end())
    {
        conflictObjList.erase(procceesor);
    }
}
/// <summary>
/// デバッグ用の球当たり判定を見せる
/// </summary>
void ConflictManager::DrawCollisionSphere()
{
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
       HitCheckExamineObjectInfo info = (*objIte)->GetHitExamineCheckInfo();
        DrawSphere3D(info.pos, info.radius, 4, GetColor(200, 200, 200), GetColor(200, 200, 200), false);
    }
}

/// <summary>
/// 引数のオブジェクトとぶつかっているか調べる
/// </summary>
/// <param name="examineObjInfo"></param>
/// <returns></returns>
std::list<ConflictExamineResultInfo> ConflictManager::GetConflictObjInfo(ConflictProccesor* conflictProccesor)
{
    std::list<ConflictExamineResultInfo> nowHitList;
    ConflictExamineResultInfo examineResultInfo = {};
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        //引数のオブジェクトそのものと当たってたらスルー
        if (conflictProccesor != (*objIte))
        {
            //当たっているか調べる
            examineResultInfo = (*objIte)->HitCheck(conflictProccesor->GetHitExamineCheckInfo());
            //ぶつかっているなら
            if (examineResultInfo.hit != HitSituation::NotHit)
            {
                if (conflictMap.contains(conflictProccesor))
                {
                    //リストに登録済みか
                    if (IsContainsConflictList(conflictProccesor, (*objIte)))
                    {
                        //すでにしている物なら当たり続けている
                        examineResultInfo.hit = HitSituation::Stay;
                    }
                    else
                    {
                        //リストに登録
                        conflictMap[conflictProccesor].push_back((*objIte));
                    }
                }
                else
                {
                    //初めて当たっているならmapに追加
                    std::list<ConflictProccesor*> list;
                    list.push_back((*objIte));
                    conflictMap.insert(std::make_pair(conflictProccesor,list));
                }
                //当たった情報を追加
                nowHitList.push_back(examineResultInfo);
            }
            //今当たってないけどぶつかったことのあるものなら
            if (IsContainsConflictList(conflictProccesor, (*objIte)))
            {
                //さっきまで当たってたけど当たらなくなったのでリストから消去
                auto containIte = std::find(conflictMap[conflictProccesor].begin(), conflictMap[conflictProccesor].end(),(*objIte));
                conflictMap[conflictProccesor].erase(containIte);
                //さっきまで当たってたやつは離れた判定
                examineResultInfo.hit = HitSituation::Exist;
                //離れた判定のものも追加
                nowHitList.push_back(examineResultInfo);
            }
        }
    }
    return nowHitList;
}

bool ConflictManager::IsContainsConflictList(ConflictProccesor* proccesor, ConflictProccesor* pastProccesor)
{
    for (auto ite = conflictMap[proccesor].begin(); ite != conflictMap[proccesor].end(); ite++)
    {
        if ((*ite) == pastProccesor)
        {
            return true;
        }
    }
    return false;
}


void ConflictManager::Update()
{
    for (auto objIte = conflictObjList.begin(); objIte != conflictObjList.end(); objIte++)
    {
        (*objIte)->ConflictProccess(GetConflictObjInfo((*objIte)));
    }
}
