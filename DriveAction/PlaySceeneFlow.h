#pragma once
#include "PlaySceeneFlowEnum.h"
#include "UIManager.h"
#include "LacerManager.h"
#include "Timer.h"
#include "PlaySceneCamera.h"
class PlaySceeneFlow
{
public:
    PlaySceeneFlow();
    ~PlaySceeneFlow();
    PlaySceeneFlowMode Update();
    void Draw();
private:
    UIManager* uiManager;
    LacerManager* lacerManager;
    PlaySceeneFlowMode nowMode;
    Timer* timer;
    PlaySceneCamera* camera;
};