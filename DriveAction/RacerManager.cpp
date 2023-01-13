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
    //コースの情報とかを引数からもらう
    CircuitData circuitData{ courceDataLoader->GetCheckPointPosList(),courceDataLoader->GetCheckPointDirList() };
    std::list<VECTOR> firstPosList = courceDataLoader->GetFirstPosList();
    std::list<VECTOR>::iterator firstPosIte = firstPosList.begin();
    //プレイヤーの初期化処理
    Racer racer{};
    racer.rank = 0;
    racer.checkPoint = new CheckPoint(circuitData);
    racer.car = new Player(*firstPosIte,courceDataLoader->GetFirstDir());
    racerList.push_back(racer);
    player = &racerList.front();

    //他の車の初期化処理
    ArgumentConflictInfo conflictInfo;
    for (int i = cpuNum; i > 0; i--)
    {
        firstPosIte++;
        racer.checkPoint = new CheckPoint(circuitData);
        racer.car = new CPUCar(*firstPosIte,courceDataLoader->GetFirstDir());
        racer.rank = 0;
        racerList.push_back(racer);
        conflictInfo.SetObjInfo(false,racer.checkPoint);
        racer.car->ConflictProcess(conflictInfo);
    }
}
//デストラクタ
RacerManager::~RacerManager()
{
    for (int i = 0; i < static_cast<signed>(racerList.size()); i++)
    {
        SAFE_DELETE(racerList.front().car);
        SAFE_DELETE(racerList.front().checkPoint);
    }
}
/// <summary>
/// 車乗りたちの更新
/// </summary>
/// <param name="deltaTime">フレーム間の経過時間</param>
/// <param name="circuit">走るコース</param>
void RacerManager::RacerUpdate(const float deltaTime, CircuitTrack* circuit)
{
    std::list<Racer>::iterator racerIte;
    Racer racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        ArgumentConflictInfo conflictInfo;
        //車の更新　コース外に出たかどうか第二引数で調べる
        racer.car->Update(deltaTime, circuit->GetOutsideHitFlag(racer.car));
        //チェックポイントの更新の更新
        conflictInfo.SetObjInfo(true, racer.car);
        //車がチェックポイントを通過したか調べる
        if (racer.checkPoint->CheckPointUpdate(conflictInfo))
        {
            //車に次の目的地を伝える
            conflictInfo.SetObjInfo(true, racer.checkPoint);
            racer.car->ConflictProcess(conflictInfo);
        }
        //コースの塀とかにぶつかったか調べる
        conflictInfo = circuit->GetCourceConflictInfo(racer.car);
        if (conflictInfo.hitFlag)
        {
            //ぶつかってたら衝突処理
            racer.car->ConflictProcess(conflictInfo);
        }
    }
}
/// <summary>
/// 引数の物体にぶつかったか調べる
/// </summary>
/// <param name="obj">調べたい物体</param>
void RacerManager::ArgumentConflictProcess(Object* obj)
{
    ArgumentConflictInfo conflictInfo;
    conflictInfo.SetObjInfo(false,obj);
    std::list<Racer>::iterator racerIte;
    Racer racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //car自身と当たり判定取ってたら通らない
        if (racer.car != obj)
        {
            //当たってるか調べる　
            if (hitChecker.HitCheck(racer.car, obj))
            {
                racer.car->ConflictProcess(conflictInfo);
            }
        }
    }
}
void RacerManager::RacerRankUpdate()
{
    std::list<Racer>::iterator racerIte;
    std::list<Racer> tempRacerList = racerList;
    Racer* racer;
    int maxTransitCheckPoint = 0;
    int transitCheckPoint = 0;
    float maxDistance = 0;
    float distance = 0;
    for (racerIte = tempRacerList.begin(); racerIte != tempRacerList.end(); racerIte++)
    {
        racer = &(*racerIte);
        transitCheckPoint= racer->checkPoint->GetTransitCheckPointCount();
        if (transitCheckPoint > maxTransitCheckPoint)
        {
            std::swap(*racer,*tempRacerList.begin());
        }
    }
    int racerNum = racerList.size();
    for (racerIte = tempRacerList.begin(); racerIte != tempRacerList.end(); racerIte++)
    {
        racer = &(*racerIte);
        for (std::list<Racer>::iterator racerIte2 = racerList.begin(); racerIte2 != racerList.end(); racerIte2++)
        {
            Racer* racer2 = &(*racerIte2);
            if (racer->car == racer2->car)
            {
                racer2->rank = racerNum;
            }
        }
        racerNum--;
    }
}
/// <summary>
/// 車乗りたち同士でぶつかってないか調べる
/// </summary>
void RacerManager::RacerConflictProcces()
{
    std::list<Racer>::iterator racerIte;
    Racer racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        ArgumentConflictProcess(racer.car);
    }
}
/// <summary>
/// プレイヤーのゴールした回数を返す
/// </summary>
/// <returns></returns>
int RacerManager::GetPlayerGoalCount()
{
    return player->checkPoint->GetGoalCount();
}

int RacerManager::GetPlayerRank()
{
    return player->rank;
}

/// <summary>
  /// 描画
  /// </summary>
  /// <returns></returns>
void RacerManager::Draw()
{
    std::list<Racer>::iterator racerIte;
    Racer racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer.car->Draw();
    }
}
/// <summary>
/// 一番最初に追加したオブジェクトを返す
/// </summary>
/// <returns></returns>
Object* RacerManager::GetPlayerCar() const
{
    Car* playerCar= player->car;
    return playerCar;
}

