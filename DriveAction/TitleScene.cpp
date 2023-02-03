#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{
    titleSceneFlow = new TitleSceeneFlow();
    fadeInFadeOut = new FadeInFadeOut();
    fadeInFadeOut->FadeInStart();
    timer = new Timer();
}

TitleScene::~TitleScene()
{
    SAFE_DELETE(titleSceneFlow);
}

SceneType TitleScene::Update()
{
    
    timer->Update();
    switch (fadeInFadeOut->GetFadeMode())
    {
    case FadeMode::fadeInStart:
        fadeInFadeOut->FadeIn(timer->GetDeltaTime());
        break;
    case FadeMode::fadeInEnd:
        titleSceneFlow->Update(timer->GetDeltaTime());
        if (titleSceneFlow->GetIsProccessEnd())
        {
            fadeInFadeOut->FadeOutStart();
        }
        break;
    case FadeMode::fadeOutStart:
        fadeInFadeOut->FadeOut(timer->GetDeltaTime());
        break;
    case FadeMode::fadeOutEnd:
        return SceneType::PLAY;
        break;
    default:
        break;
    }    return nowScenType;
}

void TitleScene::Draw()
{
#ifdef _DEBUG
#endif // _DEBUG
    titleSceneFlow->Draw();
    fadeInFadeOut->Draw();
}
