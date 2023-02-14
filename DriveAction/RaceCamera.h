#pragma once
#include "DxLib.h"
#include "PlaySceneCamaeraArgumentInfo.h"
//�v���C���[�N���X�̑O���錾
class RaceCamera final
{
public:
    RaceCamera();
    ~RaceCamera();

    void Update(PlaySceneCameraArgumentInfo argumentInfo, float deltaTime);
    void Update(float deltaTime);
private:
    //�J�����̈ʒu
    VECTOR position = {};
    //�J�����̌���
    VECTOR direction = {};
    //�v���C���[�܂ł̋���Y
    const float betweenPlayerY = 11.0f;
    //�v���C���[�܂ł̋���X
    const float betweenPlayerX = 24.0f;
    //�v���C���[�܂ł̋���Z
    const float betweenPlayerZ = 24.0f;
    //�`�悵�悤�Ƃ���͈�
    const float setNearValue = 0.1f;
    //�`�悵�悤�Ƃ���͈�
    const float setFarValue = 6000.0f;
    //�J�����̑_����܂ł̋����̑傫��
    const float aimBetween = 30.0f;
    //�J�������Ԃ̕��Ɍ������x
    const float cameraRotateSpeed = 3.2f;
};

