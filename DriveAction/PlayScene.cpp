#include "PlayScene.h"
#include "DxLib.h"
PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
    ActorMana = new ActorManager();
    PlayerActor = new Player();
    ActorMana->AddActor(*PlayerActor);
}

PlayScene::~PlayScene()
{
    delete ActorMana;
    delete PlayerActor;
}

SceneType PlayScene::Update()
{
    ActorMana->UpdateActors();
    if (CheckHitKey(KEY_INPUT_A))
    {
        NowScenType = SceneType::RESULT;
    }
    return NowScenType;
}

void PlayScene::Draw()
{
#ifdef _DEBUG
    printfDx("PlayScene\nPress:A -> ResultScene\n");
#endif // _DEBUG
    ActorMana->DrawActors();
}
