#include "ResultScene.h"
#include "DxLib.h"
#include "Utility.h"
ResultScene::ResultScene()
    :SceneBase(SceneType::RESULT)
{
    resultSceneFlow = new ResultSceneFlow();
    timer = new Timer();
}

ResultScene::~ResultScene()
{
    SAFE_DELETE(resultSceneFlow);
    SAFE_DELETE(timer);
}

SceneType ResultScene::Update()
{
    
    resultSceneFlow->Update(timer->GetDeltaTime());
    if (CheckHitKey(KEY_INPUT_W))
    {
        nowScenType = SceneType::TITLE;
    }
    timer->Update();
    return nowScenType;
}

void ResultScene::Draw()
{
#ifdef _DEBUG
#endif // _DEBUG
    resultSceneFlow->Draw();
}
