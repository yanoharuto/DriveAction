#include "TitleScene.h"
#include "DxLib.h"
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{
}

TitleScene::~TitleScene()
{
}

SceneType TitleScene::Update()
{
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
}
