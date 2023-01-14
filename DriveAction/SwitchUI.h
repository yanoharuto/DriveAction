#pragma once
#include "StringUI.h"
#include "DxLib.h"
#include <string>
class SwitchUI
{
public:
    SwitchUI();
    ~SwitchUI();
    void Update(float deltaTime);
    void Draw();
private:
    float x = 0.0f;
    float y = 0.0f;
    float time = 0.0f;
    const float span = 2.0f;
    bool isEndGoalUI = false;
    int smallPleaseSpaceKeyUINum = -1;
    int bigPleaseSpaceKeyUINum = -1;
    unsigned int bigPleaseSpaceKeyUIColor = GetColor(255, 255, 255);
    unsigned int smallPleaseSpaceKeyUIColor = GetColor(55, 55, 55);
    const int bigPleaseSpaceKeySize = 64;
    const int smallPleaseSpaceKeySize = 56;
    std::string pleaseSpaceKeyUIString = "PleaseSpaceKey";
    StringUI* bigUI;
    StringUI* smallUI;
};

