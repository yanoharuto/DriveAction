#include "ResultScene.h"
#include "DxLib.h"
#include "Utility.h"
ResultScene::ResultScene()
    :SceneBase(SceneType::RESULT)
{
    nextSceneType = SceneType::TITLE;
    sceneFlow = new ResultSceneFlow();
    fadeInFadeOut->FadeInStart();
}

ResultScene::~ResultScene()
{
}