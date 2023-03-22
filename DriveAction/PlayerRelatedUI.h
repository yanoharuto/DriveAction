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
    ~PlayerRelatedUI();
    void Update(PlayerRelatedInfo relatedInfo,float deltaTime);
    void Draw();
private:
    StringUI* timeUI;
    const int fadeValue = 85;
    const float eraseLength = 4;
};