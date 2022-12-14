#include "PlaySceneCamera.h"
#include "Player.h"
PlaySceneCamera::PlaySceneCamera()
{
    //奥行0.1〜1000までをカメラの描画範囲とする
    SetCameraNearFar(nearBetween, farBetween);
    position = {};
}

PlaySceneCamera::~PlaySceneCamera()
{
}

void PlaySceneCamera::Update(const Object* const player)
{
    VECTOR playerPos = player->GetPos();
    // lerp
    VECTOR aimPos = VAdd(playerPos, VScale(player->GetDir(), -30.0f));
    aimPos = VAdd(aimPos, VGet(0, betweenPlayerY, -betweenPlayerZ));
    position= aimPos;
    position.z -= 5.0f;
    //
    //VECTOR playerPos = _Player.GetPos();
    //VECTOR aimPos = VAdd(playerPos, VScale(_Player.GetDir(), -30.0f));
    //aimPos = VAdd(aimPos, VGet(0, 25, 0));// カメラに位置を反映.
    //position= aimPos;
    SetCameraPositionAndTarget_UpVecY(position, playerPos);
}