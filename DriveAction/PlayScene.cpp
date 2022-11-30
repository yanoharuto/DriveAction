#include "PlayScene.h"
#include "DxLib.h"
PlayScene::PlayScene()
    :SceneBase(SceneType::PLAY)
{
}

PlayScene::~PlayScene()
{
}

SceneType PlayScene::Update()
{
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
}
