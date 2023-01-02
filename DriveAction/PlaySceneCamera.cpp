#include "PlaySceneCamera.h"
#include "Player.h"
PlaySceneCamera::PlaySceneCamera()
{
    //���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
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
    //aimPos = VAdd(aimPos, VGet(0, 25, 0));// �J�����Ɉʒu�𔽉f.
    //position= aimPos;
    SetCameraPositionAndTarget_UpVecY(position, playerPos);
}