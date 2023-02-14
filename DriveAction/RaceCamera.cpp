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

void RaceCamera::Update(PlaySceneCameraArgumentInfo argumentInfo,float deltaTime)
{
    //�����̍X�V
    VECTOR tempDir = VScale(VSub(argumentInfo.dir, direction), cameraRotateSpeed * deltaTime);
    direction = VAdd(direction, tempDir);
    //�J�����̈ʒu�̍X�V
    position = argumentInfo.pos;
    position.y += betweenPlayerY;
    position.x += -(direction.x * betweenPlayerX);
    position.z += -(direction.z * betweenPlayerZ);
    //�J�����̑_���Ă���W
    VECTOR aimPos = VAdd(argumentInfo.pos, VScale(direction, aimBetween));
    SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
    SetCameraPositionAndTarget_UpVecY(position, aimPos);
    
}

void RaceCamera::Update(float deltaTime)
{
}
