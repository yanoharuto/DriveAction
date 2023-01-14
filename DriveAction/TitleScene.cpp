#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{
    titleSceneFlow = new TitleSceeneFlow();
    timer = new Timer();
}

TitleScene::~TitleScene()
{
    SAFE_DELETE(titleSceneFlow);
    SAFE_DELETE(timer);
}

SceneType TitleScene::Update()
{
    timer->Update();
    titleSceneFlow->Update(timer->GetDeltaTime());
    if (CheckHitKey(KEY_INPUT_Z))
    {
        nowScenType = SceneType::PLAY;
    }
    return nowScenType;
}

void TitleScene::Draw()
{
#ifdef _DEBUG
#endif // _DEBUG
    titleSceneFlow->Draw();
}
