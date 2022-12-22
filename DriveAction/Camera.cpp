#include "Camera.h"
#include "Player.h"
PlaySceneCamera::PlaySceneCamera()
    :Position({})
{
    //‰œs0.1`1000‚Ü‚Å‚ğƒJƒƒ‰‚Ì•`‰æ”ÍˆÍ‚Æ‚·‚é
    SetCameraNearFar(nearBetween, farBetween);
}

PlaySceneCamera::~PlaySceneCamera()
{
}

void PlaySceneCamera::Update(const Player& player)
{
    VECTOR playerPos = player.GetPos();
    // lerp
    VECTOR aimPos = VAdd(playerPos, VScale(player.GetDir(), -30.0f));
    aimPos = VAdd(aimPos, VGet(0, betweenPlayerY, -betweenPlayerZ));
    Position = aimPos;
    Position.z -= 5.0f;
    //
    //VECTOR playerPos = _Player.GetPos();
    //VECTOR aimPos = VAdd(playerPos, VScale(_Player.GetDir(), -30.0f));
    //aimPos = VAdd(aimPos, VGet(0, 25, 0));// ƒJƒƒ‰‚ÉˆÊ’u‚ğ”½‰f.
    //Position = aimPos;
    SetCameraPositionAndTarget_UpVecY(Position, playerPos);
}