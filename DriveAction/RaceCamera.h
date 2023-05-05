#pragma once
#include "DxLib.h"
#include <vector>
class ObjectObserver;
class ObjectSubject;
class RacerManager;
class RaceCamera final
{
public:
    RaceCamera(RacerManager* manager);
    ~RaceCamera();
    void Update();
private:
    //�J�����̈ʒu
    VECTOR position = {};
    //�J�����̌���
    VECTOR direction = {};
    //�v���C���[�܂ł̋���Y
    const float betweenPlayerY = 50.0f;
    //�v���C���[�܂ł̋���X
    const float betweenPlayerX = 370.0f;
    //�v���C���[�܂ł̋���Z
    const float betweenPlayerZ = 370.0f;
    //�`�悵�悤�Ƃ���͈�
    const float setNearValue = 15.0f;
    //�`�悵�悤�Ƃ���͈�
    const float setFarValue = 10700.0f;
    //�J�����̑_����܂ł̋����̑傫��
    const float aimBetween = 30.0f;
    //�J�������Ԃ̕��Ɍ������x
    const float cameraRotateSpeed = 0.043f;
    //�v���C���[�̈ʒu�������Ă������
    std::vector<ObjectObserver*> playerObserverVec;
};

