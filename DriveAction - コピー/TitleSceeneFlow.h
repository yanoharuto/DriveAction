#pragma once
#include "SceneFlowBase.h"
#include "StageSelect.h"
#include "CourceDataLoader.h"
#include "SwitchUI.h"
#include "ImgUI.h"
#include "StringUI.h"
/// <summary>
/// タイトルシーンの処理の流れ
/// </summary>
class TitleSceeneFlow :public SceneFlowBase
{
public:
    TitleSceeneFlow();
    ~TitleSceeneFlow();
    void Update(float deltaTime) override;
    void Draw() override;
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
};