#pragma once
#include "SceneBase.h"
#include "TitleSceeneFlow.h"
class TitleScene final :
    public SceneBase
{
public:
    TitleScene();
    ~TitleScene()override;

    SceneType Update() override;
    void Draw() override;
private:
    TitleSceeneFlow* titleSceneFlow;
};

