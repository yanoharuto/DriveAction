#include "RaceCamera.h"
#include "OriginalMath.h"
#include "ObjectObserver.h"
#include "ObjectSubject.h"
#include "SubjectInfoCentor.h"
#include "RacerManager.h"

RaceCamera::RaceCamera(RacerManager* manager)
{
    SetCameraNearFar(setNearValue, setFarValue);
    ObjectObserver* playerObserver = SubjectInfoCentor::GetObjectObserver(manager->GetPlayerSubject(0));
    playerObserverVec.push_back(playerObserver);
    position = {};
}

RaceCamera::~RaceCamera()
{
    playerObserverVec.clear();
}

void RaceCamera::Update()
{

    for (int i = 0; i < playerObserverVec.size(); i++)
    {
        //�����̍X�V
        VECTOR tempDir = VScale(VSub(playerObserverVec[i]->GetSubDir(), direction), cameraRotateSpeed);
        direction = VNorm(VAdd(direction, tempDir));
        //�J�����̈ʒu�̍X�V
        position = playerObserverVec[i]->GetSubPos();
        position.y += betweenPlayerY;
        position.x += -(direction.x * betweenPlayerX);
        position.z += -(direction.z * betweenPlayerZ);
        //�J�����̑_���Ă���W
        VECTOR aimPos = VAdd(position, VScale(direction, aimBetween));

        //�ʒu���m��
        SetCameraPositionAndTarget_UpVecY(position, aimPos);
    }
}
