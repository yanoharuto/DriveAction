#pragma once
#include "SceneBase.h"
class ResultScene final:
    public SceneBase
{
public:
    ResultScene();
    ~ResultScene()override;

    SceneType Update() override;
    void Draw() override;
private:
};

