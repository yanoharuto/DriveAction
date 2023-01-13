#pragma once
#include "UIManager.h"
class PostGoalDirection
{
public:
    PostGoalDirection();
    PostGoalDirection(UIManager* uimanager);
    ~PostGoalDirection();
    bool Update(float deltaTime,UIManager* uimanager);

private:
    float x = 0.0f;
    const float goalMoveX = 230.0f;
    int y = 0.0f;
    const int goalFontRed = 200;
    const int goalFontBlue = 0;
    const int goalFontGreen = 200;
    int goalMarkerNum = 0;
};

