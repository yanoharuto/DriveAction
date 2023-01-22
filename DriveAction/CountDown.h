#pragma once
#include <string>
#include "StringUI.h"
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
    int fiveTime = 5;
    std::string count;
    StringUI* countDownUI;
};

