#include "PlayScene.h"
#include "Timer.h"
#include "Player.h"
#include "PlaySceneCamera.h"
#include "SkyDome.h"
#include "CircuitTrack.h"
#include "Goal.h"
#include "Utility.h"
#include "ColiderChecker.h"
#include "CPUCar.h"
#include <functional>

PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    player = new Player();
    cpuCar = new CPUCar();
    camera = new PlaySceneCamera();
    skyDome = new SkyDome();
    circuit = new CircuitTrack(player);
    goal = new Goal(1,"goalStatus.txt");
    cpuGoal= new Goal(1,"goalStatus.txt");
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
    SAFE_DELETE(cpuGoal);
    SAFE_DELETE(timer);
    SAFE_DELETE(coliderChecker);
    SAFE_DELETE(cpuCar);
}

SceneType PlayScene::Update()
{
    float deltaTime = timer->GetDeltaTime();
    player->Update(deltaTime, circuit->GetOutsideHitFlag(player));
    cpuCar->ConflictProcess(cpuGoal);
    cpuCar->Update(deltaTime,circuit->GetOutsideHitFlag(cpuCar));
    camera->Update(player);
    coliderChecker->CheckConflictStage(player,goal);
    coliderChecker->CheckConflictStage(cpuCar,cpuGoal);
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
    cpuCar->Draw();
}
