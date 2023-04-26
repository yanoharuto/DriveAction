#pragma once

#include <string>

#include "UIManager.h"
class Timer;
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
    //収集物のアイコン
    UIData collectIconData;
    //ゲームの目標
    UIData gamePuroseData;

    int iconIncrement;
};