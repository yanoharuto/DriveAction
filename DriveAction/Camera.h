#pragma once
#include "DxLib.h"

//プレイヤークラスの前方宣言
class Player;

class PlaySceneCamera
{
public:
    PlaySceneCamera();
    ~PlaySceneCamera();

    void Update(const Player& player);
    //ポジションのgetter/setter.
    const VECTOR& GetPos() const { return Position; }

private:
    VECTOR Position;
    const float betweenPlayerY = 14.0f;
    const float betweenPlayerZ = 0.5f;
    const float nearBetween = 0.1f;
    const float farBetween = 3000.0f;
};

