#pragma once
#include <string>
#include "SceneFlowBase.h"
#include "StageSelect.h"
#include "CourceDataLoader.h"
#include "SwitchUI.h"
#include "ImgUI.h"
#include "StringUI.h"
#include "StageManager.h"
#include "SoundPlayer.h"
/// <summary>
/// タイトルシーンの処理の流れ
/// </summary>
class TitleSceeneFlow :public SceneFlowBase
{
public:
    TitleSceeneFlow();
    ~TitleSceeneFlow();
    void Update() override;
    void Draw() override;
private:
    //BGMのパス
    const std::string BGMPass = "alex.mp3";
    //ステージの情報
    StageSelect* stageSelect;
    CourceDataLoader* courceDataLoader;
    StageManager* stageManager;
    
    SwitchUI* switchUI;
    ImgUI* titleLogo;
    const float logoSize = 1.0f;
    const float setNearValue = 0.1f;
    const float setFarValue = 10000.0f;
    UIData uiData;
};