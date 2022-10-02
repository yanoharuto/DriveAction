#pragma once
#include "SceneBase.h"
class PlayScene final:
    private SceneBase
{
public:
    PlayScene();
    ~PlayScene() override;

    SceneType Update() override;
    void Draw() override;
private:
    
};

