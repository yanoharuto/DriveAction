#pragma once
#include <list>
#include "PlayerRelatedInfo.h"
#include "Utility.h"
#include "UIManager.h"
class MiniMap;
class TimerUI;
class Timer;
class NumUI;
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
    UIData manualData;
    //スラッシュ
    UIData slashHandle;
    //所得したコインの枚数についてのUIの描画位置
    int coinUIDrawX = UI_SCREEN_WIDTH * 15;
    //所得したコインの枚数についてのUIの描画位置
    int coinUIDrawY = static_cast<int>(UI_SCREEN_HEIGHT * 8);
    
    //フォントのサイズ
    const int fontSize = 1;
};