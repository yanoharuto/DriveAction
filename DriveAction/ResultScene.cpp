#include "ResultScene.h"
#include "DxLib.h"
ResultScene::ResultScene()
    :SceneBase(SceneType::RESULT)
{
}

ResultScene::~ResultScene()
{
}

SceneType ResultScene::Update()
{
    if (CheckHitKey(KEY_INPUT_W))
    {
        NowScenType = SceneType::TITLE;
    }
    return NowScenType;
}

void ResultScene::Draw()
{
#ifdef _DEBUG
    printfDx("ResultScene\nPress:W -> TitleScene\n");
#endif // _DEBUG
}
