#pragma once
#include "SceneBase.h"

class SkyDome;
class Player;
class PlaySceneCamera;
class CircuitTrack;
class Goal;
class Timer;
class ColiderChecker;
class PlayScene final:
    public SceneBase
{
public:
    PlayScene();
    ~PlayScene() override;

    SceneType Update() override;
    void Draw() override;
private:
    Player* player;
    SkyDome* skyDome;
    PlaySceneCamera* camera;
    CircuitTrack* circuit;
    Goal* goal;
    Timer* timer;
    ColiderChecker* coliderChecker;
};