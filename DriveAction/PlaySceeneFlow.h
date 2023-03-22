#pragma once
#include "EffectManager.h"
#include "FlyShipManager.h"
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
#include "ConflictManager.h"
#include "PlayerRelatedUI.h"
#include "FiringItemManager.h"
#include "DamageObjectGenerator.h"
#include "AssetManager.h"
#include "PlayerRelatedUI.h"
#include "RaceMenu.h"
#include "ShadowMap.h"
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

    //ステージのマネージャー
    StageManager* stageManager;
    //カメラ
    RaceCamera* camera;
    //コースの情報を読み取って
    CourceDataLoader* courceDataLoader;
    //スコア
    ResultScore* score;
    //ゴール後の処理
    PostGoalStaging* postGoalStaging;
    PlayerRelatedUI* playerUI;
    //デバッグ用
    CreatePosAndDirData* vecDataCreateor;
    //当たり判定処理
    ConflictManager* conflictManager;
    //エフェクト
    EffectManager* effectManager;
    //発射アイテムのマネージャー
    FiringItemManager* firingManager;
    //modelの管理
    AssetManager* modelManager;
    //途中でやめたり一時停止をする
    RaceMenu* menu;
    //今何の処理を行うか決める変数
    PlaySceeneProgress nowProgress;
    RacerManager* racerManager;
    FlyShipManager* flyShipManager;
    ShadowMap* shadowMap;
    bool isSpaceInput = false;
    float raceTime = 0;
};