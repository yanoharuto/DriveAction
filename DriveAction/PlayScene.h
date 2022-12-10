#pragma once
#include "SceneBase.h"
#include "ActorManager.h"
#include "Player.h"
class PlayScene final:
    public SceneBase
{
public:
    PlayScene();
    ~PlayScene() override;

    SceneType Update() override;
    void Draw() override;
private:
    ActorManager* ActorMana;
    Player* PlayerActor;
};

