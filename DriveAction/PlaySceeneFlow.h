#pragma once
#include "PlaySceeneProgressEnum.h"
#include "UIManager.h"
#include "RacerManager.h"
#include "Timer.h"
#include "PlaySceneCamera.h"
#include "CourceDataLoader.h"
#include "StageManager.h"
#include "CountDown.h"
#include "MiniMap.h"
#include "PostGoalDirection.h"
#include "ScoreTime.h"
/// <summary>
/// どういう順番で処理を行うか決める
/// </summary>
class PlaySceeneFlow
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    PlaySceeneFlow();
    ~PlaySceeneFlow();
    /// <summary>
    /// プレイシーンの更新
    /// </summary>
    /// <returns></returns>
    PlaySceeneProgress Update();
    /// <summary>
    /// 描画
    /// </summary>
    void Draw();
private:
    void MakeCountDownUI();
    void MakeRankUI();
    UIManager* uiManager;//uiについてのマネージャー
    RacerManager* racerManager;//車乗りのマネージャー
    StageManager* stageManager;//ステージのマネージャー
    Timer* timer;//時間経過観測
    PlaySceneCamera* camera;//カメラ
    CourceDataLoader* courceDataLoader;
    CountDown* countDown;
    MiniMap* miniMap;
    ScoreTime* scoreTime;
    PostGoalDirection* postGoalDirection;
    PlaySceeneProgress nowProgress;//今何の処理を行うか決める変数
    UIData uiData;
    int countUINum;
    const int minimapX=1080;
    const int minimapY=450;
};