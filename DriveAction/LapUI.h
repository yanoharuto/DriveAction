#pragma once
#include "StringUI.h"
class LapUI
{
public:
    LapUI();
    LapUI(int maxLap);
    ~LapUI();
    void Update(int nowLap);
    void Draw();

private:
    StringUI* lap;
    std::string maxLapString;
};

