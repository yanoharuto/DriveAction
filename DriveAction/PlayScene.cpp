#include "PlayScene.h"
#include "PlaySceneFlow.h"
#include "PlaySceeneProgressEnum.h"
#include "Utility.h"


PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    sceneFlow = new PlaySceeneFlow();
    fadeInFadeOut->FadeInStart();
}

PlayScene::~PlayScene()
{

}