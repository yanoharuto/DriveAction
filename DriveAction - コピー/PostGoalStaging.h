#pragma once
#include "UIManager.h"
#include "DxLib.h"
#include "SwitchUI.h"
#include "StringUI.h"
#include <string>
/// <summary>
/// ÉSÅ[Éãå„ÇÃââèoÇÇ∑ÇÈ
/// </summary>
class PostGoalStaging
{
public:
    PostGoalStaging();
    ~PostGoalStaging();
    bool Update(float deltaTime);
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
    StringUI* stringUI;
    const std::string clapSE = "clap.mp3";
};

