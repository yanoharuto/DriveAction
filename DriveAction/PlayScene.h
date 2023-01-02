#pragma once
#include "SceneBase.h"
class SkyDome;
class PlaySceneCamera;
class CircuitTrack;
class Timer;
class LacerManager;
class PlayScene final:
    public SceneBase
{
public:
    PlayScene();
    ~PlayScene() override;

    SceneType Update() override;
    void Draw() override;
private:

    SkyDome* skyDome;
    PlaySceneCamera* camera;
    CircuitTrack* circuit;
    Timer* timer;
    LacerManager* lacerManager;
};