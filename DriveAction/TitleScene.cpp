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
        NowScenType = SceneType::PLAY;
    }
    return NowScenType;
}

void TitleScene::Draw()
{
#ifdef _DEBUG
    printfDx("TitleScene\nPress:Z -> PlayScene\n");
#endif // _DEBUG
}
