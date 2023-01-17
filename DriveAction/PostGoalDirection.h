#pragma once
#include "UIManager.h"
#include "DxLib.h"
#include "SwitchUI.h"
#include <string>
class PostGoalDirection
{
public:
    PostGoalDirection();
    PostGoalDirection(UIManager* uimanager);
    ~PostGoalDirection();
    bool Update(float deltaTime,UIManager* uimanager);
    void Draw();
private:
    float x = 0.0f;
    float y = 0.0f;
    float time = 0.0f;
    const float goalMoveX = 730.0f;
    bool isEndGoalUI = false;
    int goalMarkerUINum = -1;

    unsigned int goalMarkerUIColor = GetColor(200, 200, 0);
    SwitchUI* switchUI;
};
