#include "PlaySceneCamera.h"
#include "Player.h"
#include "EffekseerForDXLib.h"
PlaySceneCamera::PlaySceneCamera()
{
    SetCameraNearFar(setNearValue, setFarValue);
    position = {};
}

PlaySceneCamera::~PlaySceneCamera()
{
}

void PlaySceneCamera::Update(PlaySceneCameraArgumentInfo argumentInfo)
{
    VECTOR playerPos = argumentInfo.pos;
    VECTOR playerDir = argumentInfo.dir;
    // lerp
    VECTOR aimPos = VAdd(playerPos, VScale(playerDir, aimBetween));
    position = playerPos;
    position.y = betweenPlayerY;
    position.x += -(playerDir.x * betweenPlayerX);
    position.z += -(playerDir.z * betweenPlayerZ);
    SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
    //VECTOR playerPos = _Player.GetPos();
    //VECTOR aimPos = VAdd(playerPos, VScale(_Player.GetDir(), -30.0f));
    //aimPos = VAdd(aimPos, VGet(0, 25, 0));// カメラに位置を反映.
    //position= aimPos;
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
}