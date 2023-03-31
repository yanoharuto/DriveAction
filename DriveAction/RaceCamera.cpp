#include "RaceCamera.h"
#include "OriginalMath.h"

RaceCamera::RaceCamera()
{
    SetCameraNearFar(setNearValue, setFarValue);
    position = {};
}

RaceCamera::~RaceCamera()
{
}

void RaceCamera::Update(ObjInfo argumentInfo)
{
    //向きの更新
    VECTOR tempDir = VScale(VSub(argumentInfo.dir, direction), cameraRotateSpeed);
    direction = VNorm(VAdd(direction, tempDir));
    //カメラの位置の更新
    position = argumentInfo.pos;
    position.y += betweenPlayerY * argumentInfo.modelSize;
    position.x += -(direction.x * betweenPlayerX * argumentInfo.modelSize);
    position.z += -(direction.z * betweenPlayerZ * argumentInfo.modelSize);
    //カメラの狙ってる座標
    VECTOR aimPos = VAdd(argumentInfo.pos, VScale(direction, aimBetween));
    SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
    
}

void RaceCamera::Update()
{
}
