#pragma once
#include <string>
#include "DxLib.h"
#include "ImgUI.h"
class ReverseDrivingCautionUI
{
public:
    ReverseDrivingCautionUI();
    ~ReverseDrivingCautionUI();
    void Update(VECTOR carDir,VECTOR checkPointDir,float deltaTime);
    void Draw();
private:
    UIData data = {};
    float time = 0;
    const float limitedTime = 3.0f;
    const std::string returnGraphAddress = "data/play/Return.png";
    const float graphSize = 0.2f;
    ImgUI* returnGraphUI;
};