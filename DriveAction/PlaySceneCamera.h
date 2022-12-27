#pragma once
#include "DxLib.h"
//�v���C���[�N���X�̑O���錾
class Player;
class PlaySceneCamera final
{
public:
    PlaySceneCamera();
    ~PlaySceneCamera();

    void Update(const Player* const player);

private:
    VECTOR position;
    const float betweenPlayerY = 14.0f;
    const float betweenPlayerZ = 0.5f;
    const float nearBetween = 0.1f;
    const float farBetween = 3000.0f;
};

