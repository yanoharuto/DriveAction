#pragma once
#include "StageSelect.h"
#include "UIManager.h"
#include "CourceDataLoader.h"
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
    CourceDataLoader* courceDataLoader;
    UIData uiData;
    int uiIndex;
};