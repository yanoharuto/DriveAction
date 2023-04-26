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
    //�����̃t�H���g�摜
    UIData frameData;
    UIData pointData;

    //�����_�̉摜
    int pointGraphHandle;

    //�t�H���g�摜�̃T�C�Y
    float timerFontLoadSize = 80.0f;
    float fontSize = 0;
    Timer* timer = nullptr;
    NumUI* numUI = nullptr;
};

