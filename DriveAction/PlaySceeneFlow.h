#pragma once
#include "EffectManager.h"
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
#include "RaceMenu.h"
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
    //車乗りのマネージャー
    RacerManager* racerManager;
    //ステージのマネージャー
    StageManager* stageManager;
    //カメラ
    RaceCamera* camera;
    //コースの情報を読み取って
    CourceDataLoader* courceDataLoader;
    //レース前のカウントダウン
    CountDown* countDown;
    //ミニマップ
    MiniMap* miniMap;
    //スコア
    ResultScore* score;
    //ゴール後の処理
    PostGoalStaging* postGoalStaging;
    //ギミックの処理担当
    GimmickObjManager* gimmickObjManager;
    //当たり判定処理
    ConflictProcesser* conflictProcesser;
    //プレイヤー周りのUI
    PlayerRelatedUI* playerRelatedUI;
    //エフェクト
    EffectManager* effectManager;
    //コースの情報を作る　デバッグ用
    CreatePosAndDirData* dataCreator;
    //発射アイテムのマネージャー
    FiringItemManager* firingManager;
    //ダメージ判定のあるオブジェクトの生成
    DamageObjectGenerator* damageObjGene;
    //modelの管理
    AssetManager* modelManager;
    //途中でやめたり一時停止をする
    RaceMenu* menu;
    //今何の処理を行うか決める変数
    PlaySceeneProgress nowProgress;
    
    bool isSpaceInput = false;

    float raceTime = 0;
};