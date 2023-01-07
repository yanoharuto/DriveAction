#pragma once
#include "StageSelect.h"
#include "UIManager.h"

class TitleSceeneFlow
{
public:
    TitleSceeneFlow();
    ~TitleSceeneFlow();
    void Update();
    void Draw();

private:
    void InitMinimapData();
    void InitStageString();
    StageSelect* stageSelect;
    UIManager* uiManager;
    UIData uiData;
    int uiIndex;
};