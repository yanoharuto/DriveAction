#pragma once
#include <string>
#include "Utility.h"
#include "DxLib.h"
#include "UIManager.h"
#include "ResultScore.h"
class NumUI;
class SwitchUI;
class Timer;
struct PlayerRelatedInfo;
/// <summary>
/// ゴール後の演出をする
/// </summary>
class PostGoalStaging final
{
public:
    /// <summary>
    /// ゴール後の演出をする
    /// </summary>
    PostGoalStaging();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PostGoalStaging();
    /// <summary>
    /// スコアを徐々に渡す
    /// </summary>
    /// <returns></returns>
    bool Update();
    /// <summary>
    /// スコアの描画
    /// </summary>
    void Draw();
private:
    /// <summary>
    /// スコアの表示
    /// </summary>
    struct ScoreUI
    {
        UIData data;
        int score;
    };
    //終了アナウンス
    int spaceClickCount = 0;

    //最後の瞬間の画像
    int screenGraph = -1;
    //アナウンスの移動量
    const float goalMoveX = 10.0f;
    //スペースキーを押す合間
    const float spaceKeyCoolTime = 1.5f;

    //数字の大きさ
    const float numSize = 1.3f;
    //終了のアナウンスの色
    unsigned int goalMarkerUIColor = GetColor(200, 100, 100);
    //スペースキー催促
    SwitchUI* switchUI;
    //各スコアを表示するための配列
    ScoreUI scoreUI[SCORE_KIND_NUM];
    //ゴールしたときの終了アナウンス
    //スコアの描画係
    NumUI* num;
    //タイマー
    Timer* timer;
    //スコアの数字を表示するときのX座標
    int numDrawX = UI_SCREEN_WIDTH * 15;
    //ゲーム終了時の音
    const std::string clapSE = "clap.mp3";
    //スコアを表示するときの音
    const std::string rouretteSE = "rourette.mp3";
    //スコアを表示し終わった時の音
    const std::string stopSE = "stopRourette.mp3";
    //次の処理に行く時の音
    const std::string nextSE = "Sys_Set02-pop down.mp3";
};