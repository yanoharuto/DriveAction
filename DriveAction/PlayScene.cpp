#include "PlayScene.h"
#include "PlaySceeneFlow.h"
#include "PlaySceeneProgressEnum.h"
#include "Utility.h"


PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    playSceneFlow = new PlaySceeneFlow();
}

PlayScene::~PlayScene()
{
    SAFE_DELETE(playSceneFlow);
}

SceneType PlayScene::Update()
{
    if (playSceneFlow->Update() == PlaySceeneProgress::end)
    {
        return SceneType::RESULT;
    }
    return nowScenType;
}

void PlayScene::Draw()
{
    playSceneFlow->Draw();
}
