#pragma once
#include "PlaySceeneProgressEnum.h"
#include "UIManager.h"
#include "LacerManager.h"
#include "Timer.h"
#include "PlaySceneCamera.h"
#include "StageManager.h"
class PlaySceeneFlow
{
public:
    PlaySceeneFlow();
    ~PlaySceeneFlow();
    PlaySceeneProgress Update();
    void Draw();
private:
    UIManager* uiManager;
    LacerManager* lacerManager;
    StageManager* stageManager;
    Timer* timer;
    PlaySceneCamera* camera;

    PlaySceeneProgress nowProgress;
};