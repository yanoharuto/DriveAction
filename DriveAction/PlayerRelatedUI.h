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
    ItemUI* itemUI;
    ReverseDrivingCautionUI* reverseDrivingCautionUI;
    AccelMeter* accelMeter;
};