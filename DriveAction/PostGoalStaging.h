#pragma once
#include <string>
#include "Utility.h"
#include "Timer.h"
#include "DxLib.h"
#include "SwitchUI.h"
#include "StringUI.h"
#include "PlayerRelatedInfo.h"
#include "NumUI.h"
#include "ResultScore.h"
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
    ~PostGoalStaging();
    bool Update();
    void Draw();
private:
    struct ScoreUI
    {
        UIData data;
        int score;
    };

    float x = 0.0f;
    float y = 0.0f;
    //終了アナウンス
    int spaceClickCount = 0;

    //最後の瞬間の画像
    int screenGraph = -1;
    //アナウンスの移動量
    const float goalMoveX = 10.0f;
    //スペースキーを押す合間
    const float spaceKeyCoolTime = 1.5f;
    //スコアの種類の大きさ
    const float scoreSize = 0.7f;

    //数字の大きさ
    const float numSize = 1.3f;
    //終了のアナウンスの色
    unsigned int goalMarkerUIColor = GetColor(200, 100, 100);
    //スペースキー催促
    SwitchUI* switchUI;
    //終了のアナウンス
    StringUI* stringUI;
    ScoreUI scoreUI[SCORE_KIND_NUM];
    //スコアの描画係
    NumUI* num;
    Timer* timer;
    int numDrawX = UI_SCREEN_WIDTH * 14.0f;
    const std::string clapSE = "clap.mp3";
    const std::string rouretteSE = "rourette.mp3";
    const std::string stopSE = "stopRourette.mp3";
};

