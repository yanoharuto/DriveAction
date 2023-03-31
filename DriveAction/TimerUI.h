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

    //�����̃t�H���g�摜�̃p�X
    const std::string timerFontPass = "data/NumFont.png";
    const std::string framePass = "data/timerFrame.png";
    int frameHandle;
    //�����_�̉摜
    const std::string pointFontPass = "data/Point.png";
    //�����̃t�H���g�摜
    int numGraphHandle[TIMER_FONT_NUM];
    //�����_�̉摜
    int pointGraphHandle;
    //�t�H���g�摜�̃T�C�Y
    const float timerFontLoadSize = 80.0f;

    float drawX = 0;
    float drawY = 0;
    float fontSize = 0;
    Timer* timer = nullptr;
};

