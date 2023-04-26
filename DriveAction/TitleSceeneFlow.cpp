#include "TitleSceeneFlow.h"
#include "Utility.h"
#include "StageDataAddressStruct.h"
#include "DataAddresLoader.h"
#include "DxLib.h"
#include "StageSelect.h"
#include "CourceDataLoader.h"
#include "SwitchUI.h"
#include "StageManager.h"
#include "SoundPlayer.h"
#include "UIManager.h"
TitleSceeneFlow::TitleSceeneFlow()
{
    uiManager = new UIManager();
    stageSelect = new StageSelect();  
    courceDataLoader = new CourceDataLoader();
    switchUI = new SwitchUI();
    titleLogoData = UIManager::CreateUIData(tilteLogo);
    stageManager = new StageManager();
    SetCameraNearFar(setNearValue, setFarValue);
    SoundPlayer::LoadSound(BGMPass);
}

TitleSceeneFlow::~TitleSceeneFlow()
{
    SAFE_DELETE(stageManager);
    SAFE_DELETE(stageSelect);
    SAFE_DELETE(switchUI);
    SAFE_DELETE(uiManager);
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
    DrawRotaGraph(titleLogoData.x, titleLogoData.y, titleLogoData.size, 0, titleLogoData.dataHandle[0], true, false);
}
