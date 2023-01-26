#pragma once
#include "LapUI.h"
#include "ReverseDrivingCautionUI.h"
#include "PlayerRelatedInfo.h"
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
    ReverseDrivingCautionUI* reverseDrivingCautionUI;
};