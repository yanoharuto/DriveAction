#include "RacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
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
    //コースの情報とかを引数からもらう
    CircuitData circuitData{ courceDataLoader->GetCheckPointPosList(),courceDataLoader->GetCheckPointDirList() };
    std::list<VECTOR> firstPosList = courceDataLoader->GetCarFirstPosList();
    //最初の一行は向く方向なので消す
    firstPosList.erase(firstPosList.begin());
    //ポジションのイテレーター
    std::list<VECTOR>::iterator firstPosIte = firstPosList.begin();
    //プレイヤーの初期化処理
    RacerRankInfo rankInfo{};
    player = {};
    for (int i = 0; i < racerNum + 1; i++)
    {
        firstPosIte++;
        racerInstanceArray[i].checkPoint = new CheckPoint(circuitData);
        racerInstanceArray[i].soundPlayer = new SoundPlayer();
        racerInstanceArray[i].rank = 0;
        if (i == 0)
        {
            racerInstanceArray[i].car = new Player(*firstPosIte, courceDataLoader->GetCarFirstDir(),racerInstanceArray[i].checkPoint->GetPos(),racerInstanceArray[i].soundPlayer);
         
            player.car = racerInstanceArray[i].car;
            player.rank = &racerInstanceArray[i].rank;
            player.checkPoint = racerInstanceArray[i].checkPoint;
        }
        else
        {

            racerInstanceArray[i].car = new CPUCar(*firstPosIte, courceDataLoader->GetCarFirstDir(), racerInstanceArray[i].checkPoint->GetPos(), racerInstanceArray[i].soundPlayer);

        }
        racerList.push_front(&racerInstanceArray[i]);
        rankInfo.checkPointP = racerInstanceArray[i].checkPoint;
        rankInfo.rankP = &racerInstanceArray[i].rank;
        racerRankList.push_front(rankInfo);
    }
}
//デストラクタ
RacerManager::~RacerManager()
{
    for (int i = 0; i < racerList.size(); i++)
    {
        SAFE_DELETE(racerInstanceArray[i].car);
        SAFE_DELETE(racerInstanceArray[i].checkPoint);
        SAFE_DELETE(racerInstanceArray[i].soundPlayer);
    }
}
/// <summary>
/// 車乗りたちの更新
/// </summary>
/// <param name="deltaTime">フレーム間の経過時間</param>
/// <param name="circuit">走るコース</param>
void RacerManager::RacerUpdate(const float deltaTime, CircuitTrack* circuit)
{
    std::list<Racer*>::iterator racerIte;
    Racer* racer;
    bool hitFlag;
    NeighborhoodInfo neighInfo;
    HitCheckExamineObjectInfo racerHitCheckExamineInfo;
    ConflictExamineResultInfo conflictResultInfo;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;

        racerHitCheckExamineInfo.SetExamineInfo(*racer->car);
        //周りに何があるか調べる
        hitFlag = circuit->GetOutsideHitFlag(racerHitCheckExamineInfo);
        neighInfo = circuit->GetOutsideExamineInfo(racerHitCheckExamineInfo);
        //車の更新　
        racer->car->Update(deltaTime, hitFlag,racer->checkPoint->GetPos(),racer->soundPlayer);
        //更新後の情報をもらう
        racerHitCheckExamineInfo.SetExamineInfo(*racer->car);
        //車がチェックポイントを通過したか調べる
        conflictResultInfo = racer->checkPoint->CheckPointUpdate(racerHitCheckExamineInfo);
        if (conflictResultInfo.hitFlag)
        {
            //車に次の目的地を伝える
            racer->car->ConflictProcess(deltaTime, conflictResultInfo,racer->soundPlayer);
        }
    }
}
/// <summary>
/// 引数の物体にぶつかったか調べる
/// </summary>
/// <param name="obj">調べたい物体</param>
void RacerManager::ArgumentConflictProcess(float deltaTime,Racer* obj)
{
    ConflictExamineResultInfo conflictInfo;
    conflictInfo.SetObjInfo(false,obj->car);
    std::list<Racer*>::iterator racerIte;
    Racer* racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //car自身と当たり判定取ってたら通らない
        if (racer->car != obj->car)
        {
            //当たってるか調べる　
            if (hitChecker.HitCheck(racer->car, obj->car))
            {
                conflictInfo.hitFlag = true;
                ConflictExamineResultInfo conflictInfo2;
                conflictInfo2.SetObjInfo(true, racer->car);
                racer->car->ConflictProcess(deltaTime, conflictInfo, racer->soundPlayer);
                obj->car->ConflictProcess(deltaTime,conflictInfo2,obj->soundPlayer);
            }
        }
    }
}
void RacerManager::RacerRankUpdate()
{
    RacerRankInfo* swapRankInfo = nullptr;
    int transitCheckCount = 0;//チェックポイント通過回数
    int maxTransitCheckCount = 0;//チェックポイント最大通過回数
    float checkPointBetween = 0;//次のチェックポイントまでの距離距離
    float minCheckPointBetween = 0;//次のチェックポイントまでの現状の最短距離
    //ソート
    for (auto rankIte = racerRankList.begin(); rankIte != racerRankList.end(); rankIte++)
    {   
        minCheckPointBetween = (*rankIte).checkPointP->GetCheckPointDistance();
        maxTransitCheckCount= (*rankIte).checkPointP->GetTransitCheckPointCount();
        swapRankInfo = nullptr;
        for (auto rankIte2 = rankIte; rankIte2 != racerRankList.end(); rankIte2++)
        {
            transitCheckCount = (*rankIte2).checkPointP->GetTransitCheckPointCount();
            checkPointBetween = (*rankIte2).checkPointP->GetCheckPointDistance();
            //チェックポイントがより近くて
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
    }
    //順位更新
    int rank = 0;
    for (auto rankIte = racerRankList.begin(); rankIte != racerRankList.end(); rankIte++)
    {
        *(*rankIte).rankP = ++rank;
    }
}
/// <summary>
/// 車乗りたち同士でぶつかってないか調べる
/// </summary>
void RacerManager::RacerConflictProcces(ConflictProcesser* conflictProcesser,CircuitTrack* circuit,float deltaTime)
{
    std::list<Racer*>::iterator racerIte;
    Racer* racer;
    HitCheckExamineObjectInfo racerHitCheckExamineInfo;
    ConflictExamineResultInfo conflictResultInfo;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        ArgumentConflictProcess(deltaTime, racer);

        //加速床とかにぶつかってたら
        racerHitCheckExamineInfo.SetExamineInfo(*racer->car);
        conflictResultInfo = conflictProcesser->GetConflictObjInfo(racerHitCheckExamineInfo);
        if (conflictResultInfo.hitFlag)            //ぶつかってたら衝突処理
        {
            racer->car->ConflictProcess(deltaTime, conflictResultInfo, racer->soundPlayer);
        }
        //コースの塀にぶつかったか調べる
        conflictResultInfo = circuit->GetCourceConflictInfo(racerHitCheckExamineInfo);
        if (conflictResultInfo.hitFlag)            //ぶつかってたら衝突処理
        {
            racer->car->ConflictProcess(deltaTime, conflictResultInfo, racer->soundPlayer);
        }

    }
}
/// <summary>
/// プレイヤーのゴールした回数を返す
/// </summary>
/// <returns></returns>
int RacerManager::GetPlayerGoalCount()
{
    return player.checkPoint->GetGoalCount();
}

int RacerManager::GetPlayerRank()
{
    return *player.rank;
}

PlayerRelatedInfo RacerManager::GetPlayerRelatedInfo()
{
    PlayerRelatedInfo relatedInfo = {};
    relatedInfo.carDirection = player.car->GetDir();
    relatedInfo.nextCheckPointDirection = player.checkPoint->GetDir();
    relatedInfo.lap = player.checkPoint->GetGoalCount();
    relatedInfo.rank = *player.rank;
    relatedInfo.accelPower = player.car->GetAccelPowerPercent();
    return relatedInfo;
}


/// <summary>
  /// 描画
  /// </summary>
  /// <returns></returns>
void RacerManager::Draw()
{
    std::list<Racer*>::iterator racerIte;
    Racer* racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer->car->Draw();
    }
}

Object* RacerManager::GetPlayerCar() const
{
    Car* playerCar= player.car;
    return playerCar;
}

