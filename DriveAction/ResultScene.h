#pragma once
#include "SceneBase.h"
#include "ResultSceneFlow.h"
#include "Timer.h"
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

