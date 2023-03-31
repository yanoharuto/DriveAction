#pragma once
#include "PlayerRelatedInfo.h"
#include "TimerUI.h"
#include "Utility.h"
#include "UIDataStruct.h"
#include "MiniMap.h"
#include "NumUI.h"
/// <summary>
/// プレイヤーに関係のあるUI
/// </summary>
class PlayerRelatedUI final
{
public:
    PlayerRelatedUI(Timer* setTimer,int setFirstCoinNum);
    ~PlayerRelatedUI();
    /// <summary>
    /// ミニマップの更新　やコインの枚数を更新
    /// </summary>
    /// <param name="relatedInfo"></param>
    /// <param name="setCoinPosList"></param>
    void Update(PlayerRelatedInfo relatedInfo,std::list<VECTOR> setCoinPosList);
    /// <summary>
    /// 描画
    /// </summary>
    void Draw();
private:
    //操作説明の画像
    const std::string manualPass = "data/Manual.png";
    // /これの画像のパス
    const std::string slash = "data/slash.png";
    //スラッシュ
    int slashHandle = -1;
    //最初のコインの枚数
    int firstCoinNum = 0;
    // プレイヤーが所得した枚数
    int nowGetCoinNum = 0;
    //タイマー
    TimerUI* timerUI;
    //ミニマップ
    MiniMap* minimapUI;
    //コインの枚数を描画するクラス
    NumUI* numUI;
    //操作説明のUI情報
    UIData manualData{ UI_SCREEN_WIDTH * 2,UI_SCREEN_HEIGHT * 10 ,-1};
    //コインの枚数についてのUIの描画位置
    float coinUIDrawX = UI_SCREEN_WIDTH * 15;
    //コインの枚数についてのUIの描画位置
    float coinUIDrawY = UI_SCREEN_HEIGHT * 8;
    //フォント画像のサイズ
    const float timerFontLoadSize = 80.0f;
    //描画位置
    const float drawTimerX = UI_SCREEN_WIDTH * 17;
    //描画位置
    const float drawTimerY = UI_SCREEN_HEIGHT * 4;
    //フォントのサイズ
    const float fontSize = 1.0f;
};