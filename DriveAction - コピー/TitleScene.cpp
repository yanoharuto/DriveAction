#include "TitleScene.h"
#include "DxLib.h"
#include "Utility.h"
TitleScene::TitleScene()
    :SceneBase(SceneType::TITLE)
{

    sceneFlow = new TitleSceeneFlow();
    fadeInFadeOut->FadeInStart();
}

TitleScene::~TitleScene()
{
}