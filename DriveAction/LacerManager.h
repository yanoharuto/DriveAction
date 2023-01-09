#pragma once
#include <List>
#include <string>
#include "HitChecker.h"
class CourceDataLoader;
class Object;
class CheckPoint;
class Car;
class CircuitTrack;
/// <summary>
/// 当たり判定で使う渡してほしい情報
/// Actorに定義
/// </summary>
struct  ArgumentConflictInfo;
/// <summary>
/// 走ってる車の情報
/// </summary>
struct Racer
{
    int rank;
    CheckPoint* checkPoint;
    Car* car;
};
/// <summary>
/// 車乗りのマネージャー
/// </summary>
class RacerManager
{
public:

    RacerManager() {};
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="lacerNum">車乗りの数だけリストに追加するよ</param>
    /// <returns></returns>
    RacerManager(int cpuNum, CourceDataLoader* const courceDataLoader);
    //デストラクタ
    ~RacerManager();
    /// <summary>
    /// 車乗りたちの更新
    /// </summary>
    /// <param name="deltaTime">フレーム間の経過時間</param>
    /// <param name="circuit">走るコース</param>
    void Update(const float deltaTime, CircuitTrack* circuit);
    /// <summary>
    /// 引数の物体にぶつかったか調べる
    /// </summary>
    /// <param name="obj"></param>
    void ArgumentConflictProcess(Object* obj);

    /// <summary>
    /// 描画
    /// </summary>
    /// <returns></returns>
    void Draw();
    /// <summary>
    /// 一番最初に追加したオブジェクトを返す
    /// </summary>
    /// <returns></returns>
    Object* GetPlayer() const;
    /// <summary>
    /// 車乗りたち同士でぶつかってないか調べる
    /// </summary>
    void LacerConflictProcces();

private:
    //車乗り達のリスト
    std::list<Racer> RacerList;
    //当たってるかどうか調べる
    HitChecker hitChecker;
};

