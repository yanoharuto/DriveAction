#pragma once
#include <string>
#include "DxLib.h"
#include "ImgUI.h"
/// <summary>
/// ‹t‘–’†‚ÌUI
/// </summary>
class ReverseDrivingCautionUI
{
public:
    ReverseDrivingCautionUI();
    ~ReverseDrivingCautionUI();
    void Update(bool reverse,float deltaTime);
    void Draw();
private:
    UIData data = {};
    float time = 0;
    const float limitedTime = 2.0f;
    const std::string returnGraphAddress = "data/play/Return.png";
    const std::string returnSoundAddress = "alert.mp3";
    const float graphSize = 0.3f;
    ImgUI* returnGraphUI;
};