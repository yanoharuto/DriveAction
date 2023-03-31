#include "RacerManager.h"
#include "CPU.h"
#include "Player.h"
#include "CheckPoint.h"
#include "PlayerCar.h"
#include "Utility.h"
#include "RacerGenerater.h"
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
    playerInfoCenter = new PlayerInformationCenter();
    //走る人たちを生成
    RacerGenerater* racerGenerater = new RacerGenerater();
    racerGenerater->CreateRacers(racerNum, &racerList, &player,playerInfoCenter);

    //プレイヤーの初期化処理
    RacerRankInfo rankInfo{};

    for (auto i = racerList.begin(); i != racerList.end(); i++)
    {
        //ランク情報を追加
        rankInfo.checkPointP = (*i)->GetCheckPointer();
        rankInfo.rankP = (*i)->GetRankPointer();
        racerRankList.push_front(rankInfo);
    }
    SAFE_DELETE(racerGenerater);
    
}
//デストラクタ
RacerManager::~RacerManager()
{
    for (auto ite = racerList.begin(); ite != racerList.end(); ite++)
    {
        SAFE_DELETE((*ite));
    }
    SAFE_DELETE(playerInfoCenter);
}
/// <summary>
/// 車乗りたちの更新
/// </summary>
/// <param name="deltaTime">フレーム間の経過時間</param>
/// <param name="circuit">走るコース</param>
void RacerManager::RacerUpdate( )
{
    Racer* racer;
    ConflictExamineResultInfo conflictResultInfo;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //車の更新　
        racer->Update();
    }
    //位置情報とか更新
    playerInfoCenter->UpdatePlayerRelatedInfo();
}
/// <summary>
/// 上下に動く
/// </summary>
void RacerManager::UpDown()
{
    Racer* racer;
    for (auto racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer->UpDown();
    }
}

/// <summary>
/// プレイヤーのUIに必要な情報を渡す
/// </summary>
/// <returns></returns>
PlayerInformationCenter* RacerManager::GetPlayerRelatedInfo()
{
   return playerInfoCenter;
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

ObjInfo RacerManager::GetPlayerCarPosDir() 
{
    return player->GetPlayerPosAndDir();
}