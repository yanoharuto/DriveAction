#pragma once
#include <string>
#include "Timer.h"
#define TIMER_FONT_NUM 10

class TimerUI
{
public:
    TimerUI();
    TimerUI(float setX,float setY,float setFontSize,Timer* setTimer);
    ~TimerUI();

    void Draw();
private:

    //数字のフォント画像のパス
    const std::string timerFontPass = "data/NumFont.png";
    const std::string framePass = "data/timerFrame.png";
    int frameHandle;
    //小数点の画像
    const std::string pointFontPass = "data/Point.png";
    //数字のフォント画像
    int numGraphHandle[TIMER_FONT_NUM];
    //小数点の画像
    int pointGraphHandle;
    //フォント画像のサイズ
    const float timerFontLoadSize = 80.0f;

    float drawX = 0;
    float drawY = 0;
    float fontSize = 0;
    Timer* timer = nullptr;
};

