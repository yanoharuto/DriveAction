#include "PlayScene.h"
#include "DxLib.h"
#include "ActorManager.h"
#include "Player.h"
#include "Camera.h"
#include "SkyDome.h"
#include "CircuitTrack.h"

PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    actorManager = new ActorManager();
    playerActor = new Player();
    camera = new PlaySceneCamera();
    skyDome = new SkyDome();
    circuit = new CircuitTrack();
    time = GetNowCount();
    deltaTime = deltaTimeCalculationLine;
}

PlayScene::~PlayScene()
{
    delete actorManager;
    delete playerActor;
    delete camera;
    delete skyDome;
    delete circuit;
}

SceneType PlayScene::Update()
{
    /*printfDx("%f::", time);
    printfDx("%d\n", GetNowCount());*/
    deltaTime = GetNowCount() - time;
    deltaTime /= 1000;
    time = GetNowCount();
    
    if (deltaTime >= deltaTimeCalculationLine)
    {
        //�v���C���[�̍X�V
        playerActor->Update(deltaTime);
        //�J�����Ƀv���C���[�̈ʒu��������
        camera->Update(*playerActor);
        if (CheckHitKey(KEY_INPUT_A))
        {
            nowScenType = SceneType::RESULT;
        }
    }
    else
    {
        printfDx("%f", deltaTime);
    }

    return nowScenType;
}

void PlayScene::Draw()
{
#ifdef _DEBUG
#endif // _DEBUG
    playerActor->Draw();
    skyDome->Draw();
    circuit->Draw();
}
