#include "RacerManager.h"
#include "CPU.h"
#include "Player.h"
#include "CheckPoint.h"
#include "PlayerCar.h"
#include "Utility.h"
#include "CircuitTrack.h"
#include "CourceDataLoader.h"
#include "PlayerRelatedInfo.h"
/// <summary>
/// 初期化
/// </summary>
/// <param name="racerNum">車乗りの数だけリストに追加するよ</param>
/// <returns></returns>
RacerManager::RacerManager(int cpuNum, CourceDataLoader* const courceDataLoader)
{
    racerNum = cpuNum > maxRacerNum ? maxRacerNum : cpuNum;
    std::list<VECTOR> firstPosList = courceDataLoader->GetCarFirstPosList();
    //最初の一行は向く方向なので消す
    firstPosList.erase(firstPosList.begin());
    //ポジションのイテレーター
    auto firstPosIte = firstPosList.begin();
    //プレイヤーの初期化処理
    RacerRankInfo rankInfo{};
    Racer* newRacer;
    //コースの情報とかを引数からもらう
    VECTOR firstDir = courceDataLoader->GetCarFirstDir();
    CircuitData circuitData{ courceDataLoader->GetCheckPointPosList(),courceDataLoader->GetCheckPointDirList() };
    //レーサーの数だけNewする
    for (int i = 0; i < racerNum + 1; i++)
    {
        firstPosIte++;
        if (i == 0)
        {
            player = new Player(circuitData, *firstPosIte, firstDir);
            newRacer = player;
        }
        else
        {
            newRacer = new CPU(circuitData, *firstPosIte, firstDir);
        }
        racerList.push_front(newRacer);
        //ランク情報を追加
        rankInfo.checkPointP = newRacer->GetCheckPointer();
        rankInfo.rankP = newRacer->GetRankPointer();
        racerRankList.push_front(rankInfo);
    }
}
//デストラクタ
RacerManager::~RacerManager()
{
    for (auto ite = racerList.begin(); ite != racerList.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
}
/// <summary>
/// 車乗りたちの更新
/// </summary>
/// <param name="deltaTime">フレーム間の経過時間</param>
/// <param name="circuit">走るコース</param>
void RacerManager::RacerUpdate(const float deltaTime, CircuitTrack* circuit, DamageObjectGenerator* damageObj)
{
    Racer* racer;
    bool hitFlag;
    ConflictExamineResultInfo conflictResultInfo;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //周りに何があるか調べる
        hitFlag = circuit->GetOutsideHitFlag(racer->GetCarHitCheckExamineInfo());
        //車の更新　
        racer->Update(deltaTime, hitFlag, damageObj);
    }
}
/// <summary>
/// 引数の物体にぶつかったか調べる
/// </summary>
/// <param name="obj">調べたい物体</param>
void RacerManager::ArgumentConflictProcess(float deltaTime,Racer* obj)
{
    Racer* racer;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //car自身と当たり判定取ってたら通らない
        if (racer!= obj)
        {
            //当たってるか調べる　
            if (racer->HitCheck(obj->GetCarHitCheckExamineInfo()))
            {
                //ぶつかった相手にも情報を渡す
                ConflictExamineResultInfo resultInfo = obj->GetConflictExamineResultInfo();
                resultInfo.hitFlag = true;
                racer->ConflictProcces(resultInfo, deltaTime);
                resultInfo = racer->GetConflictExamineResultInfo();
                resultInfo.hitFlag = false;
                obj->ConflictProcces(resultInfo,deltaTime);
            }
        }
    }
}
void RacerManager::RacerRankUpdate()
{
    int transitCheckCount = 0;//チェックポイント通過回数
    int maxTransitCheckCount = 0;//チェックポイント最大通過回数
    float checkPointBetween = 0;//次のチェックポイントまでの距離距離
    float minCheckPointBetween = 0;//次のチェックポイントまでの現状の最短距離
    int rank = 0;
    //ソート
    for (auto rankIte = racerRankList.begin(); rankIte != racerRankList.end(); rankIte++)
    {   
        minCheckPointBetween = (*rankIte).checkPointP->GetCheckPointDistance();//チェックポイントまでの差を出す
        maxTransitCheckCount = (*rankIte).checkPointP->GetTransitCheckPointCount();//通過回数を出す
        RacerRankInfo* swapRankInfo = nullptr;//↑二つの変数が更新されたら中身も更新
        for (auto rankIte2 = rankIte; rankIte2 != racerRankList.end(); rankIte2++)
        {
            transitCheckCount = (*rankIte2).checkPointP->GetTransitCheckPointCount();
            checkPointBetween = (*rankIte2).checkPointP->GetCheckPointDistance();
            //チェックポイントにより近くて
            if (checkPointBetween < minCheckPointBetween)
            {
                //チェックポイントを通過した回数が多い人がより高順位
                if (transitCheckCount >= maxTransitCheckCount)
                {
                    minCheckPointBetween = checkPointBetween;
                    maxTransitCheckCount = transitCheckCount;
                    swapRankInfo = &(*rankIte2);
                }
            }
        }
        //スワップ
        if (swapRankInfo != nullptr)
        {
            std::swap((*rankIte), *swapRankInfo);
        }
        //順位更新
        *(*rankIte).rankP = ++rank;
    }
}
/// <summary>
/// レーサーの当たり判定処理
/// </summary>
void RacerManager::RacerConflictProcces(ConflictProcesser* conflictProcesser,CircuitTrack* circuit,float deltaTime)
{
    Racer* racer;
    ConflictExamineResultInfo conflictResultInfo;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //車同士でぶつかってないか調べる
        ArgumentConflictProcess(deltaTime, racer);

        //加速床とかにぶつかってたら
        conflictResultInfo = conflictProcesser->GetConflictObjInfo(racer->GetCarHitCheckExamineInfo());
        if (conflictResultInfo.hitFlag)
        {
            racer->ConflictProcces(conflictResultInfo, deltaTime);
        }
        //コースの塀にぶつかったか調べる
        conflictResultInfo = circuit->GetCourceConflictInfo(racer->GetCarHitCheckExamineInfo());
        if (conflictResultInfo.hitFlag)            //ぶつかってたら衝突処理
        {
            racer->ConflictProcces(conflictResultInfo,deltaTime);
        }

    }
}



/// <summary>
/// プレイヤーのUIに必要な情報を渡す
/// </summary>
/// <returns></returns>
PlayerRelatedInfo RacerManager::GetPlayerRelatedInfo()
{
   return player->GetRelatedInfo();
}


/// <summary>
  /// 描画
  /// </summary>
  /// <returns></returns>
void RacerManager::Draw()
{
    Racer* racer;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer->Draw();
    }
}

PlaySceneCameraArgumentInfo RacerManager::GetPlayerCarPosDir() 
{
    return player->GetCameraArgumentInfo();
}

