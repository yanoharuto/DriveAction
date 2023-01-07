#include "LacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"
#include "StageSelect.h"
#include "StageDataAddressStruct.h"
#include "VECTOR3Loader.h"
/// <summary>
/// 初期化
/// </summary>
/// <param name="lacerNum">車乗りの数だけリストに追加するよ</param>
/// <returns></returns>
LacerManager::LacerManager(int cpuNum,std::string chekPointAddress)
{
    //プレイヤーの初期化処理
    Lacer lacer{};
    lacer.rank = 0;
    lacer.checkPoint = new CheckPoint(chekPointAddress.c_str());
    lacer.car = new Player();
    lacerList.push_back(lacer);
    //他の車の初期化処理
    ArgumentConflictInfo conflictInfo;
    for (int i = cpuNum; i > 0; i--)
    {
        lacer.checkPoint = new CheckPoint(lacerList.front().checkPoint->GetCheckPoint());
        lacer.car = new CPUCar( );
        lacer.rank = 0;
        lacerList.push_back(lacer);
        conflictInfo.SetObjInfo(false,lacer.checkPoint);
        lacer.car->ConflictProcess(conflictInfo);
    }
}
//デストラクタ
LacerManager::~LacerManager()
{
    for (int i = 0; i < static_cast<signed>(lacerList.max_size()); i++)
    {
        SAFE_DELETE(lacerList.front().car);
        SAFE_DELETE(lacerList.front().checkPoint);
    }
}
/// <summary>
/// 車乗りたちの更新
/// </summary>
/// <param name="deltaTime">フレーム間の経過時間</param>
/// <param name="circuit">走るコース</param>
void LacerManager::Update(const float deltaTime,CircuitTrack* circuit)
{
    void(LacerManager::*function)(Lacer, float, CircuitTrack*);
    function = &LacerManager::LacerUpdateProcces;
    LacerLoop(function,deltaTime,circuit);
}
/// <summary>
/// 引数の物体にぶつかったか調べる
/// </summary>
/// <param name="obj">調べたい物体</param>
void LacerManager::ArgumentConflictProcess(Object* obj)
{
    ArgumentConflictInfo conflictInfo;
    conflictInfo.SetObjInfo(false,obj);
    std::list<Lacer>::iterator lacerIte;
    Lacer lacer;
    for (lacerIte = lacerList.begin(); lacerIte != lacerList.end(); lacerIte++)
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
void LacerManager::LacerConflictProcces()
{
    std::list<Lacer>::iterator lacerIte;
    Lacer lacer;
    for (lacerIte = lacerList.begin(); lacerIte != lacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        ArgumentConflictProcess(lacer.car);
    }
}

void LacerManager::LacerUpdateProcces(Lacer lacer, float deltaTime,CircuitTrack* circuit)
{
    ArgumentConflictInfo conflictInfo;
    //車の更新　コース外に出たかどうか第二引数で調べる
    lacer.car->Update(deltaTime, circuit->GetOutsideHitFlag(lacer.car));
    //チェックポイントの更新の更新
    conflictInfo.SetObjInfo(true, lacer.car);
    lacer.checkPoint->Update(conflictInfo);
    //車に次のチェックポイントが何処か調べる
    if (hitChecker.HitCheck(lacer.car, lacer.checkPoint))
    {
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

void LacerManager::LacerLoop(void(LacerManager::* function)(Lacer))
{
    std::list<Lacer>::iterator lacerIte;
    ArgumentConflictInfo conflictInfo;
    for (lacerIte = lacerList.begin(); lacerIte != lacerList.end(); lacerIte++)
    {
       (this->(*function))(*lacerIte);
    }
}

void LacerManager::LacerLoop(void(*function)(Lacer, float, CircuitTrack*), float deltaTime, CircuitTrack* circuit)
{
}


/// <summary>
  /// 描画
  /// </summary>
  /// <returns></returns>
void LacerManager::Draw()
{
    std::list<Lacer>::iterator lacerIte;
    Lacer lacer;
    for (lacerIte = lacerList.begin(); lacerIte != lacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        lacer.car->Draw();
    }
}
/// <summary>
/// 一番最初に追加したオブジェクトを返す
/// </summary>
/// <returns></returns>
Object* LacerManager::GetPlayer() const
{
    return lacerList.front().car;
}

