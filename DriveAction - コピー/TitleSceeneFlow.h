#pragma once
#include "SceneFlowBase.h"
#include "StageSelect.h"
#include "CourceDataLoader.h"
#include "SwitchUI.h"
#include "ImgUI.h"
#include "StringUI.h"
/// <summary>
/// �^�C�g���V�[���̏����̗���
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