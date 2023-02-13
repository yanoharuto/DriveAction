#pragma once
#include "DxLib.h"
#include "PlaySceneCamaeraArgumentInfo.h"
//�v���C���[�N���X�̑O���錾
class PlaySceneCamera final
{
public:
    PlaySceneCamera();
    ~PlaySceneCamera();

    void Update(PlaySceneCameraArgumentInfo argumentInfo);
    void Update(float deltaTime);
private:
    VECTOR position;
    
    const float betweenPlayerY = 11.0f;
    const float betweenPlayerX = 24.0f;
    const float betweenPlayerZ = 24.0f;
    const float setNearValue = 0.1f;
    const float setFarValue = 6000.0f;
    const float aimBetween = 30.0f;
};

