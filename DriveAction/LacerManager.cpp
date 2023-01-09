#include "LacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"
#include "StageSelect.h"
#include "StageDataAddressStruct.h"
#include "VECTOR3Loader.h"
#include "CourceDataLoader.h"
/// <summary>
/// 初期化
/// </summary>
/// <param name="lacerNum">車乗りの数だけリストに追加するよ</param>
/// <returns></returns>
RacerManager::RacerManager(int cpuNum, CourceDataLoader* const courceDataLoader)
{
    //プレイヤーの初期化処理
    CircuitData circuitData{ courceDataLoader->GetCheckPointPosList(),courceDataLoader->GetCheckPointDirList() };
    std::list<VECTOR> firstPosList = courceDataLoader->GetFirstPosList();
    std::list<VECTOR>::iterator firstPosIte = firstPosList.begin();
    Racer racer{};
    racer.rank = 0;
    racer.checkPoint = new CheckPoint(circuitData);
    racer.car = new Player(*firstPosIte,courceDataLoader->GetFirstDir());
    RacerList.push_back(racer);
    //他の車の初期化処理
    ArgumentConflictInfo conflictInfo;
    for (int i = cpuNum; i > 0; i--)
    {
        firstPosIte++;
        racer.checkPoint = new CheckPoint(circuitData);
        racer.car = new CPUCar(*firstPosIte,courceDataLoader->GetFirstDir());
        racer.rank = 0;
        RacerList.push_back(racer);
        conflictInfo.SetObjInfo(false,racer.checkPoint);
        racer.car->ConflictProcess(conflictInfo);
    }
}
//デストラクタ
RacerManager::~RacerManager()
{
    for (int i = 0; i < static_cast<signed>(RacerList.max_size()); i++)
    {
        SAFE_DELETE(RacerList.front().car);
        SAFE_DELETE(RacerList.front().checkPoint);
    }
}
/// <summary>
/// 車乗りたちの更新
/// </summary>
/// <param name="deltaTime">フレーム間の経過時間</param>
/// <param name="circuit">走るコース</param>
void RacerManager::Update(const float deltaTime, CircuitTrack* circuit)
{
    std::list<Racer>::iterator lacerIte;
    Racer lacer;
    for (lacerIte = RacerList.begin(); lacerIte != RacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        ArgumentConflictInfo conflictInfo;
        //車の更新　コース外に出たかどうか第二引数で調べる
        lacer.car->Update(deltaTime, circuit->GetOutsideHitFlag(lacer.car));
        //チェックポイントの更新の更新
        conflictInfo.SetObjInfo(true, lacer.car);
        //車がチェックポイントを通過したか調べる
        if (lacer.checkPoint->CheckPointUpdate(conflictInfo))
        {
            //車に次の目的地を伝える
            conflictInfo.SetObjInfo(true, lacer.checkPoint);
            lacer.car->ConflictProcess(conflictInfo);
        }
        //コースの塀とかにぶつかったか調べる
        conflictInfo = circuit->GetCourceConflictInfo(lacer.car);
        if (conflictInfo.hitFlag)
        {
            //ぶつかってたら衝突処理
            lacer.car->ConflictProcess(conflictInfo);
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
    std::list<Racer>::iterator lacerIte;
    Racer lacer;
    for (lacerIte = RacerList.begin(); lacerIte != RacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        //car自身と当たり判定取ってたら通らない
        if (lacer.car != obj)
        {
            //当たってるか調べる　
            if (hitChecker.HitCheck(lacer.car, obj))
            {
                lacer.car->ConflictProcess(conflictInfo);
            }
        }
    }
}
/// <summary>
/// 車乗りたち同士でぶつかってないか調べる
/// </summary>
void RacerManager::LacerConflictProcces()
{
    std::list<Racer>::iterator lacerIte;
    Racer lacer;
    for (lacerIte = RacerList.begin(); lacerIte != RacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        ArgumentConflictProcess(lacer.car);
    }
}

/// <summary>
  /// 描画
  /// </summary>
  /// <returns></returns>
void RacerManager::Draw()
{
    std::list<Racer>::iterator lacerIte;
    Racer lacer;
    for (lacerIte = RacerList.begin(); lacerIte != RacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        lacer.car->Draw();
    }
}
/// <summary>
/// 一番最初に追加したオブジェクトを返す
/// </summary>
/// <returns></returns>
Object* RacerManager::GetPlayer() const
{
    return RacerList.front().car;
}

