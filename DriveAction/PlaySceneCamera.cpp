#include "PlaySceneCamera.h"
#include "OriginalMath.h"

PlaySceneCamera::PlaySceneCamera()
{
    SetCameraNearFar(setNearValue, setFarValue);
    position = {};
}

PlaySceneCamera::~PlaySceneCamera()
{
}

void PlaySceneCamera::Update(PlaySceneCameraArgumentInfo argumentInfo,float deltaTime)
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

void PlaySceneCamera::Update(float deltaTime)
{
}
