#include "ResultScene.h"
#include "DxLib.h"
#include "Utility.h"
ResultScene::ResultScene()
    :SceneBase(SceneType::RESULT)
{
    resultSceneFlow = new ResultSceneFlow();
    fadeInFadeOut = new FadeInFadeOut();
    fadeInFadeOut->FadeInStart();
    timer = new Timer();
}

ResultScene::~ResultScene()
{
    SAFE_DELETE(resultSceneFlow);
}

SceneType ResultScene::Update()
{
    timer->Update();
    switch (fadeInFadeOut->GetFadeMode())
    {
    case FadeMode::fadeInStart:
        fadeInFadeOut->FadeIn(timer->GetDeltaTime());
        break;
    case FadeMode::fadeInEnd:
        resultSceneFlow->Update(timer->GetDeltaTime());
        if(resultSceneFlow->IsProccssEnd())
        {
            fadeInFadeOut->FadeOutStart();
        }
        break;
    case FadeMode::fadeOutStart:
        fadeInFadeOut->FadeOut(timer->GetDeltaTime());
        break;
    case FadeMode::fadeOutEnd:
        return SceneType::TITLE;
        break;
    default:
        break;
    }
    return nowScenType;
}

void ResultScene::Draw()
{
#ifdef _DEBUG
#endif // _DEBUG
    resultSceneFlow->Draw();
    fadeInFadeOut->Draw();
}
