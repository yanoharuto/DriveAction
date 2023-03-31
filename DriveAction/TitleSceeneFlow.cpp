#include "TitleSceeneFlow.h"
#include "Utility.h"

#include "StageDataAddressStruct.h"
#include "DataAddresLoader.h"
#include "DxLib.h"

TitleSceeneFlow::TitleSceeneFlow()
{
    stageSelect = new StageSelect();  
    courceDataLoader = new CourceDataLoader();
    switchUI = new SwitchUI();
    uiData.x = SCREEN_WIDTH / 2;
    uiData.y = SCREEN_HEIGHT / 2;
    uiData.dataHandle = LoadGraph("data/title/MachRider.png");
    titleLogo = new ImgUI(logoSize,uiData);
    stageManager = new StageManager();
    SetCameraNearFar(setNearValue, setFarValue);
    SoundPlayer::LoadSound(BGMPass);
}

TitleSceeneFlow::~TitleSceeneFlow()
{
    SAFE_DELETE(titleLogo);
    SAFE_DELETE(stageManager);
    SAFE_DELETE(stageSelect);
    SAFE_DELETE(switchUI);
    SoundPlayer::StopAllSound();
}

void TitleSceeneFlow::Update()
{
    if (!SoundPlayer::IsPlaySound(BGMPass))
    {
        SoundPlayer::Play2DSE(BGMPass);
    }
    //スカイドームを回転
    stageManager->Update();

    std::string string = stageSelect->GetLoadeStageName();
    //スペースキーの催促
    switchUI->Update();

    int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    if (key & PAD_INPUT_10)
    {
        isEndProccess = true;
        nextSceneType = SceneType::PLAY;
    }
}

void TitleSceeneFlow::Draw()
{  
    stageManager->Draw();
    switchUI->Draw();
    titleLogo->DrawUI();
}
