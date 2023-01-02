#include "PlayScene.h"
#include "Timer.h"
#include "PlaySceneCamera.h"
#include "SkyDome.h"
#include "CircuitTrack.h"
#include "Utility.h"
#include "HitChecker.h"
#include "LacerManager.h"
#include <functional>

PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    lacerManager = new LacerManager(8);
    camera = new PlaySceneCamera();
    skyDome = new SkyDome();
    circuit = new CircuitTrack(lacerManager->GetPlayer()->GetRadius());
    timer = new Timer();
}

PlayScene::~PlayScene()
{
    SAFE_DELETE(lacerManager);
    SAFE_DELETE(camera);
    SAFE_DELETE(skyDome);
    SAFE_DELETE(circuit);
    SAFE_DELETE(timer);
}

SceneType PlayScene::Update()
{
    float deltaTime = timer->GetDeltaTime();
    lacerManager->Update(deltaTime,circuit);
    lacerManager->LacerConflictProcces();
    camera->Update(lacerManager->GetPlayer());
    timer->Update();
    return nowScenType;
}

void PlayScene::Draw()
{
#ifdef _DEBUG
#endif // _DEBUG
    circuit->Draw();
    skyDome->Draw();
    lacerManager->Draw();
}
