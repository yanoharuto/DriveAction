#pragma once
#include <string>
#include "Utility.h"
#include "UIManager.h"
#include "DxLib.h"
#include "SwitchUI.h"
#include "StringUI.h"
#include "PlayerRelatedInfo.h"
#include "NumUI.h"
/// <summary>
/// ゴール後の演出をする
/// </summary>
class PostGoalStaging
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
    float x = 0.0f;
    float y = 0.0f;
    //アナウンスの移動量
    const float goalMoveX = 10.0f;
    //終了アナウンス
    bool isEndGoalUI = false;

    //最後の瞬間の画像
    int screenGraph = -1;
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
    //当たった回数のスコア
    UIData hitUI;
    //時間のスコア
    UIData timeUI;
    //スコアの合計
    UIData scoreUI;
    //コインのスコア
    UIData coinUI;
    //スコアの描画係
    NumUI* num;
    int numDrawX = UI_SCREEN_WIDTH * 14.0f;
    const std::string clapSE = "clap.mp3";
};

