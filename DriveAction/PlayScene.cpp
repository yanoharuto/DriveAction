#include "PlayScene.h"
#include "PlaySceeneFlow.h"
#include "PlaySceeneProgressEnum.h"
#include "Utility.h"


PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    playSceneFlow = new PlaySceeneFlow();
    fadeInFadeOut = new FadeInFadeOut();
    fadeInFadeOut->FadeInStart();
    timer = new Timer();
}

PlayScene::~PlayScene()
{
    SAFE_DELETE(playSceneFlow);
}

SceneType PlayScene::Update()
{
    timer->Update();
    switch (fadeInFadeOut->GetFadeMode())
    {
    case FadeMode::fadeInStart:
        fadeInFadeOut->FadeIn(timer->GetDeltaTime());
        break;
    case FadeMode::fadeInEnd:
        playSceneFlow->Update(timer->GetDeltaTime());
        if (playSceneFlow->GetIsEndProccess())
        {
            fadeInFadeOut->FadeOutStart();
        }
        break;
    case FadeMode::fadeOutStart:
        fadeInFadeOut->FadeOut(timer->GetDeltaTime());
        break;
    case FadeMode::fadeOutEnd:
        return SceneType::RESULT;
        break;
    default:
        break;
    }
    return nowScenType;
}

void PlayScene::Draw()
{
    playSceneFlow->Draw();
    fadeInFadeOut->Draw();
}
