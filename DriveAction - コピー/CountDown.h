#pragma once
#include <string>
#include "ImgUI.h"
#include "DxLib.h"
class CountDown
{
public:
    CountDown();
    ~CountDown();
    void Update(float deltaTime);
    bool CountDownEnd();
    void DrawUI();
private:
    float startTime;
    bool countDownEnd;
    bool countStart = false;
    unsigned int color;
    const int fiveTime = 5;
    std::string count;
    const std::string countDownSE = "countdown.mp3";
    const std::string graphAddress = "data/lamp.png";
    const std::string lightGraphAddress = "data/lamp";
    const std::string png = ".png";
    const unsigned int lightColor1 = GetColor( 233,73,75 );
    const unsigned int lightColor2 = GetColor( 247,190,22 );
    const unsigned int lightColor3 = GetColor( 112,179,43 );
    UIData uiData;
    int lightGraph;
    int highBrightGraph = -1;
    int downScaleGraph = -1;
    int gaussGraph = -1;
    int gaussRatio = 900;
    ImgUI* countDownUI;
};

