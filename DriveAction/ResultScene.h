#pragma once
#include "SceneBase.h"
#include "ResultSceneFlow.h"
class ResultScene final:
    public SceneBase
{
public:
    ResultScene();
    ~ResultScene()override;

    SceneType Update() override;
    void Draw() override;
private:
    ResultSceneFlow* resultSceneFlow;
};

