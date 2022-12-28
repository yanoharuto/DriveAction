#include "PlayScene.h"
#include "Timer.h"
#include "ObjectManager.h"
#include "Player.h"
#include "PlaySceneCamera.h"
#include "SkyDome.h"
#include "CircuitTrack.h"
#include "Goal.h"
#include "Utility.h"
#include "ColiderChecker.h"
#include <functional>

PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    player = new Player();
    camera = new PlaySceneCamera();
    skyDome = new SkyDome();
    circuit = new CircuitTrack(player);
    goal = new Goal(1);
    timer = new Timer();
    coliderChecker = new ColiderChecker();
}

PlayScene::~PlayScene()
{
    SAFE_DELETE(player);
    SAFE_DELETE(camera);
    SAFE_DELETE(skyDome);
    SAFE_DELETE(circuit);
    SAFE_DELETE(goal);
    SAFE_DELETE(timer);
    SAFE_DELETE(coliderChecker);
}

SceneType PlayScene::Update()
{

    player->Update(timer->GetDeltaTime(), circuit->GetOutsideHitFlag(player));
    camera->Update(player);
    coliderChecker->Check(player,goal);
     
    timer->Update();
    if (!goal->GetAliveFlag())
    {
        return SceneType::RESULT;
    }
    return nowScenType;
}

void PlayScene::Draw()
{
#ifdef _DEBUG
#endif // _DEBUG
    player->Draw();
    circuit->Draw();
    skyDome->Draw();
}
