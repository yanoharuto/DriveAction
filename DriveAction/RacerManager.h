#pragma once
#include <List>
#include <string>
#include "PlaySceneCamaeraArgumentInfo.h"
#include "ConflictProcesser.h"
#include "HitChecker.h"
#include "SoundPlayer.h"
#include "ItemHolder.h"
#include "Racer.h"
#include "Player.h"
class CourceDataLoader;
class CircuitTrack;

struct ConflictExamineResultInfo;
struct PlayerRelatedInfo;

/// <summary>
/// レーサーの順位操作に使う
/// </summary>
struct RacerRankInfo
{
    int* rankP;
    CheckPoint* checkPointP;
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
    void RacerUpdate(const float deltaTime, CircuitTrack* circuit, FiringItemManager* firingItemManager);
    /// <summary>
    /// 引数の物体にぶつかったか調べる
    /// </summary>
    /// <param name="obj"></param>
    void ArgumentConflictProcess(float deltaTime,Racer* obj);
    /// <summary>
    /// レーサーたちの順位の更新
    /// </summary>
    void RacerRankUpdate();
    /// <summary>
    /// 描画
    /// </summary>
    /// <returns></returns>
    void Draw();
    /// <summary>
    /// 一番最初に追加したオブジェクトを返す
    /// </summary>
    /// <returns></returns>
    PlaySceneCameraArgumentInfo GetPlayerCarPosDir();
    /// <summary>
    /// 車乗りたち同士でぶつかってないか調べる
    /// </summary>
    void RacerConflictProcces(ConflictProcesser* conflictProcesser, CircuitTrack* circuit, float deltaTime);
    /// <summary>
    /// プレイヤーのゴールした回数を返す
    /// </summary>
    /// <returns></returns>
    int GetPlayerGoalCount();

    /// <summary>
    /// プレイヤーの情報を渡す
    /// </summary>
    /// <returns></returns>
    PlayerRelatedInfo GetPlayerRelatedInfo();
private:
    //レーサーの最大人数
    static const int maxRacerNum = 6;
    //レーサーの数
    int racerNum = 0;
    //レーサーの配列　
   
    //racerInstanceArrayを指しているリスト
    std::list<Racer*> racerList;
    //レーサーの順位を更新するために必要なリスト
    std::list<RacerRankInfo> racerRankList;
    //当たってるかどうか調べる
    HitChecker hitChecker;
    //プレイヤーの情報
    Player* player;
};