#include "LacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="lacerNum">車乗りの数だけリストに追加するよ</param>
/// <returns></returns>
LacerManager::LacerManager(int cpuNum)
{
    Lacer lacer{};
    lacer.rank = cpuNum + 1;
    lacer.checkPoint = new CheckPoint(1, "goalStatus.txt");
    lacer.car = new Player();
    lacerList.push_back(lacer);
    for (int i = cpuNum; i > 0; i--)
    {
        lacer.car = new CPUCar();
        lacer.checkPoint = new CheckPoint(lacerList.front().checkPoint->GetCheckPoint());
        lacer.rank = i;
        lacerList.push_back(lacer);
        ArgumentConflictInfo conflictInfo = MakeArgumentInfo(lacer.checkPoint);
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
    std::list<Lacer>::iterator lacerIte;
    Lacer lacer;
    ArgumentConflictInfo conflictInfo;
    for(lacerIte = lacerList.begin();lacerIte!=lacerList.end();lacerIte++)
    {
        lacer = *lacerIte;
        //車の更新　コース外に出たかどうか第二引数で調べる
        lacer.car->Update(deltaTime, circuit->GetOutsideHitFlag(lacer.car));
        if (hitChecker.HitCheck(lacer.checkPoint,lacer.car))
        {
            lacer.checkPoint->Update(lacer.car);

            conflictInfo = MakeArgumentInfo(lacer.checkPoint);
            lacer.car->ConflictProcess(conflictInfo);
        }
        conflictInfo = circuit->GetCourceConflictInfo(lacer.car);
        if (conflictInfo.hitFlag)
        {
            lacer.car->ConflictProcess(conflictInfo);
        }
    }
}
/// <summary>
/// 引数の物体にぶつかったか調べる
/// </summary>
/// <param name="obj">調べたい物体</param>
void LacerManager::ArgumentConflictProcess(Object* obj)
{
    ArgumentConflictInfo conflictInfo = MakeArgumentInfo(obj);
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
/// <summary>
  /// 引数のオブジェクトの当たり判定情報所得
  /// </summary>
  /// <param name="obj">当たり判定を調べたいオブジェクト</param>
  /// <returns>引数として渡したい情報</returns>

ArgumentConflictInfo LacerManager::MakeArgumentInfo(Object* obj)
{
    return { true ,obj->GetTag(),obj->GetPos(),obj->GetRadius() };
}
