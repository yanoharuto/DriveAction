#pragma once
#include "SceneBase.h"

class ActorManager;
class SkyDome;
class Player;
class PlaySceneCamera;
class CircuitTrack;

class PlayScene final:
    public SceneBase
{
public:
    PlayScene();
    ~PlayScene() override;

    SceneType Update() override;
    void Draw() override;
private:
    ActorManager* actorManager;
    SkyDome* skyDome;
    Player* playerActor;
    PlaySceneCamera* camera;
    CircuitTrack* circuit;
    const float deltaTimeCalculationLine = 0.00001f;
    float time;
    float deltaTime;
};