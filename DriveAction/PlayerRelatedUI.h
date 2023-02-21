#pragma once
#include "LapUI.h"
#include "ReverseDrivingCautionUI.h"
#include "PlayerRelatedInfo.h"
#include "AccelMeter.h"
#include "ImgUI.h"
#include "ItemUI.h"
class PlayerRelatedUI
{
public:
    PlayerRelatedUI();
    PlayerRelatedUI(const int maxLap);
    ~PlayerRelatedUI();
    void Update(PlayerRelatedInfo relatedInfo,float deltaTime);
    void Draw();
private:
    LapUI* lapUI;
    StringUI* rankUI;
    StringUI* timeUI;
    StringUI* halfUI;
    ItemUI* itemUI;
    ImgUI* descriptionUI;
    ReverseDrivingCautionUI* reverseDrivingCautionUI;
    AccelMeter* accelMeter;
    const int fadeValue = 85;
    const float eraseLength = 4;
};