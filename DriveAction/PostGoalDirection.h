#pragma once
#include "UIManager.h"
#include "DxLib.h"
#include <string>
class PostGoalDirection
{
public:
    PostGoalDirection();
    PostGoalDirection(UIManager* uimanager);
    ~PostGoalDirection();
    bool Update(float deltaTime,UIManager* uimanager);

private:
    float x = 0.0f;
    float y = 0.0f;
    float time = 0.0f;
    const float goalMoveX = 230.0f;
    bool isEndGoalUI = false;
    int goalMarkerUINum = -1;
    int smallPleaseSpaceKeyUINum = -1;
    int bigPleaseSpaceKeyUINum = -1;
    unsigned int pleaseSpaceKeyUIColor = GetColor(255, 255, 255);
    unsigned int goalMarkerUIColor = GetColor(200, 200, 0);
    const int bigPleaseSpaceKeySize = 64;
    const int smallPleaseSpaceKeySize = 56;
    std::string pleaseSpaceKeyUIString = "PleaseSpaceKey";
    
};

