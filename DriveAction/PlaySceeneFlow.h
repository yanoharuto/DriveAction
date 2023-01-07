#pragma once
#include "PlaySceeneProgressEnum.h"
#include "UIManager.h"
#include "LacerManager.h"
#include "Timer.h"
#include "PlaySceneCamera.h"
#include "StageManager.h"
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
    UIManager* uiManager;//uiについてのマネージャー
    LacerManager* lacerManager;//車乗りのマネージャー
    StageManager* stageManager;//ステージのマネージャー
    Timer* timer;//時間経過観測
    PlaySceneCamera* camera;//カメラ
    PlaySceeneProgress nowProgress;//今何の処理を行うか決める変数
};