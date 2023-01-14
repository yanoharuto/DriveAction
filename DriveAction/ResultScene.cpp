#include "ResultScene.h"
#include "DxLib.h"
#include "Utility.h"
ResultScene::ResultScene()
    :SceneBase(SceneType::RESULT)
{
    resultSceneFlow = new ResultSceneFlow();
}

ResultScene::~ResultScene()
{
    SAFE_DELETE(resultSceneFlow);
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
    resultSceneFlow->Draw();
}
