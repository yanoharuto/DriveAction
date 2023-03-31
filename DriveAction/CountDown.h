#pragma once
#include <string>
#include "ImgUI.h"
#include "DxLib.h"
#include "Timer.h"
class CountDown
{
public:
    CountDown(Timer* timer);
    ~CountDown();
    void Update();
    bool CountDownEnd();
    void DrawUI();
private:
    float startTime;
    bool countDownEnd;
    bool countStart = false;
    int oneGraph;
    int twoGraph;
    int threeGraph;
    const std::string countDownSE = "countdown.mp3";
    const std::string oneGraphPass = "data/1.png";
    const std::string twoGraphPass = "data/2.png";
    const std::string threeGraphPass = "data/3.png";
    UIData uiData;
    Timer* timer;
};

