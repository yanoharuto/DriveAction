#pragma once
#include "SceneFlowBase.h"
#include "StageSelect.h"
#include "CourceDataLoader.h"
#include "SwitchUI.h"
#include "ImgUI.h"
#include "StringUI.h"
class TitleSceeneFlow
{
public:
    TitleSceeneFlow();
    ~TitleSceeneFlow();
    void Update(float deltaTime);
    void Draw();
    bool GetIsProccessEnd();
private:
    void InitMinimapData();
    void InitStageString();
    StageSelect* stageSelect;
    CourceDataLoader* courceDataLoader;
    SwitchUI* switchUI;
    StringUI* stringUI;
    ImgUI* miniMap;
    ImgUI* backGround;
    UIData uiData;
    bool isProccessEnd;
};