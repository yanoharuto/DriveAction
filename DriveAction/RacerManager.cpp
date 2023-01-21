#include "RacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"
#include "StageDataAddressStruct.h"
#include "CourceDataLoader.h"
#include <algorithm>
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
    std::list<VECTOR> firstPosList = courceDataLoader->GetFirstPosList();
    std::list<VECTOR>::iterator firstPosIte = firstPosList.begin();
    //プレイヤーの初期化処理
    RacerRankInfo rankInfo{};

    for (int i = 0; i < racerNum; i++)
    {
        firstPosIte++;
        if (i == 0)
        {
            racerInstanceArray[i].car = new Player(*firstPosIte, courceDataLoader->GetFirstDir());
            racerInstanceArray[i].rank = 0;
            racerInstanceArray[i].checkPoint = new CheckPoint(circuitData);
            player.car = racerInstanceArray[i].car;
            player.rank = &racerInstanceArray[i].rank;
            player.checkPoint = racerInstanceArray[i].checkPoint;
        }
        else
        {
            racerInstanceArray[i].car = new CPUCar(*firstPosIte, courceDataLoader->GetFirstDir());
            racerInstanceArray[i].rank = 0;
            racerInstanceArray[i].checkPoint = new CheckPoint(circuitData);
        }
        racerList.push_front(&racerInstanceArray[i]);
        rankInfo.checkPointP = racerInstanceArray[i].checkPoint;
        rankInfo.rankP = &racerInstanceArray[i].rank;
        racerRankList.push_front(rankInfo);
    }
    int* a= &racerInstanceArray[0].rank;
    player.rank;
}
//デストラクタ
RacerManager::~RacerManager()
{
    for (int i = 0; i < static_cast<signed>(racerList.size()); i++)
    {
        SAFE_DELETE(racerInstanceArray[i].car);
        SAFE_DELETE(racerInstanceArray[i].checkPoint);
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
    ConflictProccessArgumentInfo conflictInfo;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        conflictInfo.SetObjInfo(false,racer->car);
        //周りに何があるか調べる
        hitFlag = circuit->GetOutsideHitFlag(conflictInfo);
        neighInfo = circuit->GetOutsideExamineInfo(racer->car->GetNeighExamineInfo());
        //車の更新　
        racer->car->Update(deltaTime, hitFlag,neighInfo);
        //チェックポイントの更新の更新
        conflictInfo.SetObjInfo(true, racer->car);
        //車がチェックポイントを通過したか調べる
        racer->checkPoint->CheckPointUpdate(conflictInfo);
        //車に次の目的地を伝える
        conflictInfo.SetObjInfo(true, racer->checkPoint);
        racer->car->ConflictProcess(deltaTime, conflictInfo);
        //コースの塀とかにぶつかったか調べる
        conflictInfo.SetObjInfo(false, racer->car);
        conflictInfo = circuit->GetCourceConflictInfo(conflictInfo);
        if (conflictInfo.hitFlag)            //ぶつかってたら衝突処理
        {
            racer->car->ConflictProcess(deltaTime, conflictInfo);
        }
    }
}
/// <summary>
/// 引数の物体にぶつかったか調べる
/// </summary>
/// <param name="obj">調べたい物体</param>
void RacerManager::ArgumentConflictProcess(float deltaTime,Object* obj)
{
    ConflictProccessArgumentInfo conflictInfo;
    conflictInfo.SetObjInfo(false,obj);
    std::list<Racer*>::iterator racerIte;
    Racer* racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //car自身と当たり判定取ってたら通らない
        if (racer->car != obj)
        {
            //当たってるか調べる　
            if (hitChecker.HitCheck(racer->car, obj))
            {
                racer->car->ConflictProcess(deltaTime,conflictInfo);
            }
        }
    }
}
void RacerManager::RacerRankUpdate()
{
    std::list<RacerRankInfo>::iterator rankIte;
    RacerRankInfo rankInfo;
    int transitCheckCount = 0;//通過回数
    int maxTransitCheckCount = 0;//最大通過回数
    float size = 0;
    float maxSize = 0;
    for (rankIte = racerRankList.begin(); rankIte != racerRankList.end(); rankIte++)
    {
        rankInfo = *rankIte;
        transitCheckCount = rankInfo.checkPointP->GetTransitCheckPointCount();
        size = rankInfo.checkPointP->GetCheckPointDistance();
        printfDx("%d::size%d::\n", rankInfo.rankP,size);
        if (size > maxSize)
        {

            std::swap(*racerRankList.begin(), rankInfo);
            maxSize = size;
        }
    }
    int rank = racerNum;
    for (rankIte = racerRankList.begin(); rankIte != racerRankList.end(); rankIte++)
    {
        rankInfo = *rankIte;
        *rankInfo.rankP = rank;
        rank--;
    }
    printfDx("playerRank::%d::%d\n", player.rank,*player.rank);
}
/// <summary>
/// 車乗りたち同士でぶつかってないか調べる
/// </summary>
void RacerManager::RacerConflictProcces(float deltaTime)
{
    std::list<Racer*>::iterator racerIte;
    Racer* racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        ArgumentConflictProcess(deltaTime,racer->car);
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
/// <summary>
/// 一番最初に追加したオブジェクトを返す
/// </summary>
/// <returns></returns>
Object* RacerManager::GetPlayerCar() const
{
    Car* playerCar= player.car;
    return playerCar;
}

