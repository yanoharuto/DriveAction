#pragma once

#include <string>
#include "Utility.h"
#include "Timer.h"
#include "UIDataStruct.h"
/// <summary>
/// レース前の処理
/// </summary>
class RacePrevProcess
{
public:
    RacePrevProcess();
    ~RacePrevProcess();
    //更新
    void Update();
    //描画
    void Draw();
    //終了したら
    bool IsProccesEnd();
private:
    //ファンファーレの効果音のパス
    const std::string fanfareSEPass = "Fanfare.mp3";
    //ゲームの目的を表示するための画像のパス
    const std::string purposeGraph = "data/GamePurpose.png";
    //ど真ん中に表示する
    UIData purposeData = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,-1 };
     //切り替え時間
    const float visibleCoolTime = 1.0f;
    //見えているかどうか
    bool isVisible = true;
    //表示切替タイマー
    Timer* displaySwitchingTimer;
};