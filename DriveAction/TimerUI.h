#pragma once
#include <string>
#include "UIManager.h"

class Timer;
class NumUI;
class TimerUI
{
public:
    TimerUI();
    TimerUI(float setFontSize,Timer* setTimer);
    ~TimerUI();

    void Draw();
private:
    //数字のフォント画像
    UIData frameData;
    UIData pointData;

    //小数点の画像
    int pointGraphHandle;

    //フォント画像のサイズ
    float timerFontLoadSize = 80.0f;
    float fontSize = 0;
    Timer* timer = nullptr;
    NumUI* numUI = nullptr;
};

