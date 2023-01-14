#pragma once
#include "StageSelect.h"
#include "UIManager.h"
#include "CourceDataLoader.h"
#include "SwitchUI.h"
class TitleSceeneFlow
{
public:
    TitleSceeneFlow();
    ~TitleSceeneFlow();
    void Update(float deltaTime);
    void Draw();

private:
    void InitMinimapData();
    void InitStageString();
    StageSelect* stageSelect;
    UIManager* uiManager;
    CourceDataLoader* courceDataLoader;
    SwitchUI* switchUI;
    UIData uiData;
    int uiIndex;
};