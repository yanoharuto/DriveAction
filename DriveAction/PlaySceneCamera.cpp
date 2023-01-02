#include "PlaySceneCamera.h"
#include "Player.h"
PlaySceneCamera::PlaySceneCamera()
{
    //âúçs0.1Å`1000Ç‹Ç≈ÇÉJÉÅÉâÇÃï`âÊîÕàÕÇ∆Ç∑ÇÈ
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
    //aimPos = VAdd(aimPos, VGet(0, 25, 0));// ÉJÉÅÉâÇ…à íuÇîΩâf.
    //position= aimPos;
    SetCameraPositionAndTarget_UpVecY(position, playerPos);
}