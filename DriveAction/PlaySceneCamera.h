#pragma once
#include "DxLib.h"
//プレイヤークラスの前方宣言
class Object;
class PlaySceneCamera final
{
public:
    PlaySceneCamera();
    ~PlaySceneCamera();

    void Update(const Object* const player);

private:
    VECTOR position;
    const float betweenPlayerY = 14.0f;
    const float betweenPlayerZ = 0.5f;
    const float nearBetween = 0.1f;
    const float farBetween = 6000.0f;
};

