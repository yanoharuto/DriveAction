#include "PlayScene.h"
#include "PlaySceeneFlow.h"
#include "PlaySceeneProgressEnum.h"
#include "Utility.h"


PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    sceneFlow = new PlaySceeneFlow();
    nextSceneType = SceneType::RESULT;
    fadeInFadeOut->FadeInStart();
}

PlayScene::~PlayScene()
{

}