#pragma once
#include "SceneBase.h"
class TitleScene final :
    public SceneBase
{
public:
    TitleScene();
    ~TitleScene()override;

    SceneType Update() override;
    void Draw() override;
private:

};

