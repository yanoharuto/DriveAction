#pragma once
#include "CreatePosAndDirData.h"
#include "SceneFlowBase.h"
#include "SoundPlayer.h"
#include "PlaySceeneProgressEnum.h"
#include "RacerManager.h"
#include "RaceCamera.h"
#include "CourceDataLoader.h"
#include "StageManager.h"
#include "CountDown.h"
#include "MiniMap.h"
#include "PostGoalStaging.h"
#include "ResultScore.h"
#include "GimmickObjManager.h"
#include "ConflictProcesser.h"
#include "PlayerRelatedUI.h"
#include "FiringItemManager.h"
#include "DamageObjectGenerator.h"
#include "AssetManager.h"
/// <summary>
/// どういう順番で処理を行うか決める
/// </summary>
class PlaySceeneFlow final:public SceneFlowBase
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    PlaySceeneFlow();
    ~PlaySceeneFlow()override;
    /// <summary>
    /// プレイシーンの更新
    /// </summary>
    /// <returns></returns>
    void Update(float deltaTime) override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;

private:
    RacerManager* racerManager;//車乗りのマネージャー
    StageManager* stageManager;//ステージのマネージャー
    RaceCamera* camera;//カメラ
    CourceDataLoader* courceDataLoader;
    CountDown* countDown;
    MiniMap* miniMap;
    ResultScore* scoreTime;
    PostGoalStaging* postGoalStaging;
    GimmickObjManager* gimmickObjManager;
    ConflictProcesser* conflictProcesser;
    PlayerRelatedUI* playerRelatedUI;
    SoundPlayer* soundPlayer;
    CreatePosAndDirData* dataCreator;
    FiringItemManager* firingManager;
    DamageObjectGenerator* damageObjGene;
    AssetManager* assetManager;
    PlaySceeneProgress nowProgress;//今何の処理を行うか決める変数
    int countUINum;
    bool isSpaceInput = false;
    const int minimapX = 1080;
    const int minimapY = 450;
    const int maxLap = 0;
    const int racerNum = 3;
    float raceTime = 0;
    
};