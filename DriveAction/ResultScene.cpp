#include "ResultScene.h"
#include "DxLib.h"
#include "Utility.h"
ResultScene::ResultScene()
    :SceneBase(SceneType::RESULT)
{
    sceneFlow = new ResultSceneFlow();
    fadeInFadeOut->FadeInStart();
}

ResultScene::~ResultScene()
{
}