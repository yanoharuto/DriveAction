#include "TitleSceeneFlow.h"
#include "Utility.h"

#include "StageDataAddressStruct.h"
#include "DataAddresLoader.h"
#include "DxLib.h"

TitleSceeneFlow::TitleSceeneFlow()
{
    stageSelect = new StageSelect();  
    courceDataLoader = new CourceDataLoader();
    InitMinimapData();
    miniMap = new ImgUI(1.0f,uiData);
    InitStageString();
    stringUI = new StringUI(GetColor(0,0,255),uiData);
    switchUI = new SwitchUI();
    uiData.x = SCREEN_WIDTH/2;
    uiData.y = SCREEN_HEIGHT / 2;
    uiData.dataHandle = LoadGraph("data/title/titleBackGround.jpg");
    backGround = new ImgUI(1,uiData);
}

TitleSceeneFlow::~TitleSceeneFlow()
{
    SAFE_DELETE(backGround);
    SAFE_DELETE(miniMap);
    SAFE_DELETE(stringUI);
    SAFE_DELETE(stageSelect);
    SAFE_DELETE(switchUI);
}

void TitleSceeneFlow::Update(float deltaTime)
{
    std::string string = stageSelect->GetLoadeStageName();
    stringUI->UpdateString(string);
    switchUI->Update(deltaTime);
    int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    if (key & PAD_INPUT_10)
    {
        isEndProccess = true;
    }
}

void TitleSceeneFlow::Draw()
{  
    backGround->DrawUI();
    stringUI->DrawRightAlignedString();
    miniMap->DrawUI();
    switchUI->Draw();

}

void TitleSceeneFlow::InitMinimapData()
{
    uiData.x = SCREEN_WIDTH / 16 * 11;
    uiData.y = SCREEN_HEIGHT / 7 * 3;
    std::string chara = courceDataLoader->GetMiniMapImgAddress();
    uiData.dataHandle = LoadGraph(chara.c_str(),false);
}

void TitleSceeneFlow::InitStageString()
{
    uiData.x = SCREEN_WIDTH / 4 * 1;
    uiData.y = SCREEN_HEIGHT / 5 * 3;
    uiData.dataHandle = CreateFontToHandle("OCRB",64,3,DX_FONTTYPE_NORMAL);
}
