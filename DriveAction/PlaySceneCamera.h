#pragma once
#include "DxLib.h"
#include "PlaySceneCamaeraArgumentInfo.h"
//プレイヤークラスの前方宣言
class Object;
class PlaySceneCamera final
{
public:
    PlaySceneCamera();
    ~PlaySceneCamera();

    void Update(PlaySceneCameraArgumentInfo argumentInfo);

private:
    VECTOR position;
    const float betweenPlayerY = 5.0f;
    const float betweenPlayerX = 24.0f;
    const float betweenPlayerZ = 24.0f;
    const float setNearValue = 0.1f;
    const float setFarValue = 6000.0f;
    const float aimBetween = 30.0f;
};

