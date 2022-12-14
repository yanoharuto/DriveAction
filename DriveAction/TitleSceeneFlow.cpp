#include "TitleSceeneFlow.h"
#include "Utility.h"
#include "ImgUI.h"
#include "StringUI.h"
#include "StageDataAddressStruct.h"
#include "DataAddresLoader.h"
#include "DxLib.h"
TitleSceeneFlow::TitleSceeneFlow()
{
    uiManager = new UIManager();
    stageSelect = new StageSelect();  
    courceDataLoader = new CourceDataLoader();
    InitMinimapData();
    ImgUI* miniMap = new ImgUI(1.0f,uiData);
    uiManager->AddUI(miniMap);
    InitStageString();
    StringUI* stringUI = new StringUI(GetColor(0,0,255),uiData);
    uiIndex = uiManager->AddUI(stringUI);
}

TitleSceeneFlow::~TitleSceeneFlow()
{
    SAFE_DELETE(uiManager);
    SAFE_DELETE(stageSelect);
}

void TitleSceeneFlow::Update()
{
    std::string string = stageSelect->GetLoadeStageName();
    uiManager->Update(uiIndex, string);
}

void TitleSceeneFlow::Draw()
{
    uiManager->DrawUI();
}

void TitleSceeneFlow::InitMinimapData()
{
    uiData.x = 800;
    uiData.y = 400;
    std::string chara = courceDataLoader->GetMiniMapImgAddress();
    uiData.dataHandle = LoadGraph(chara.c_str(),false);
}

void TitleSceeneFlow::InitStageString()
{
    uiData.x = 300;
    uiData.y = 700;
    uiData.dataHandle = CreateFontToHandle("BIZ UD?S?V?b?N",64,3,DX_FONTTYPE_NORMAL);
}
