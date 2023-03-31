#pragma once
#include "StringUI.h"
#include "DxLib.h"
#include <string>
class SwitchUI
{
public:
    SwitchUI();
    ~SwitchUI();
    void Update();
    void Draw();
private:
    float x = 0.0f;
    float y = 0.0f;
    float time = 0.0f;
    const float span = 2.0f;
    bool isEndGoalUI = false;
    int smallPleaseSpaceKeyUINum = -1;
    int bigPleaseSpaceKeyUINum = -1;
    unsigned int bigUIColor = GetColor(235, 235, 235);
    unsigned int smalleUIColor = GetColor(85, 85, 85);
    const int bigPleaseSpaceKeySize = 64;
    const int smallPleaseSpaceKeySize = 64;
    std::string pleaseSpaceKeyUIString = "Press the space key";
    StringUI* bigUI;
    StringUI* smallUI;
};

