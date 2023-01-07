#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{
    titleSceneFlow = new TitleSceeneFlow();
}

TitleScene::~TitleScene()
{
    SAFE_DELETE(titleSceneFlow);
}

SceneType TitleScene::Update()
{
    titleSceneFlow->Update();
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
