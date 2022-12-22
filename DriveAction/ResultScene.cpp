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
        nowScenType = SceneType::TITLE;
    }
    return nowScenType;
}

void ResultScene::Draw()
{
#ifdef _DEBUG
#endif // _DEBUG
}
