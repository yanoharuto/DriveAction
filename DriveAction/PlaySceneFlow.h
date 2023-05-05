#pragma once
#include "SceneFlowBase.h"
#include <string>
#define PlaySceneProccess 4
class AssetManager;
class CountDown;
class ConflictManager;
class CourceDataLoader;
class CoinManager;
class EffectManager;
class FiringItemManager;
class FlyShipManager;
class PostGoalStaging;
class PlayerRelatedUI;
class RaceCamera;
class ResultScore;
class RaceScreen;
class RacePrevProcess;
class RacerManager;
class ShadowMap;
class StageManager;
class Timer;
class UIManager;
/// <summary>
/// どういう順番で処理を行うか決める
/// </summary>
class PlaySceneFlow final:public SceneFlowBase
{
public:
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    PlaySceneFlow();
    ~PlaySceneFlow()override;
    /// <summary>
    /// プレイシーンの更新
    /// </summary>
    /// <returns></returns>
    void Update() override;
    /// <summary>
    /// 描画
    /// </summary>
    void Draw() override;
    
private:
    /// <summary>
/// プレイシーンの段階
/// </summary>
    enum PlaySceeneProgress
    {
        start,
        game,
        playerGoal,
        end
    };
    void DrawManagers();
    void GameUpdate();
    void PlayerGoalUpdate();
    void EndUpdate();
    void StartUpdate();
    void (PlaySceneFlow::*UpdateFunc[PlaySceneProccess])();
    //ステージのマネージャー
    StageManager* stageManager;
    //カメラ
    RaceCamera* camera;
    //コースの情報を読み取って
    CourceDataLoader* courceDataLoader;
    //スコア
    ResultScore* score = nullptr;
    //ゴール後の処理
    PostGoalStaging* postGoalStaging;
    //プレイヤー関係のUI
    PlayerRelatedUI* playerUI;
    //当たり判定処理
    ConflictManager* conflictManager;
    //エフェクト
    EffectManager* effectManager;
    //発射アイテムのマネージャー
    FiringItemManager* firingManager;
    //modelの管理
    AssetManager* modelManager;
    
    //今何の処理を行うか決める変数
    PlaySceeneProgress nowProgress;
    //レース前の処理
    RacePrevProcess* racePrevProccess;
    //運転手用のマネージャー
    RacerManager* racerManager;
    //敵のオブジェクトのマネージャー
    FlyShipManager* flyShipManager;
    //ゲーム終了タイマー
    Timer* gameLimitTimer;

    //コインのマネージャー
    CoinManager* coinManager;
    //シャドウマップ
    ShadowMap* shadowMap;
    //レース中の描画した物を保存する
    RaceScreen* screen;

    UIManager* uiManager;
    //BGMのパス
    const std::string BGMPass = "movements.mp3";
    int BGMBolume = 50;
};