#pragma once

#include <string>
#include "Utility.h"
#include "Timer.h"
#include "UIDataStruct.h"
/// <summary>
/// ���[�X�O�̏���
/// </summary>
class RacePrevProcess
{
public:
    RacePrevProcess();
    ~RacePrevProcess();
    //�X�V
    void Update();
    //�`��
    void Draw();
    //�I��������
    bool IsProccesEnd();
private:
    //�t�@���t�@�[���̌��ʉ��̃p�X
    const std::string fanfareSEPass = "Fanfare.mp3";
    //�Q�[���̖ړI��\�����邽�߂̉摜�̃p�X
    const std::string purposeGraph = "data/GamePurpose.png";
    //�ǐ^�񒆂ɕ\������
    UIData purposeData = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,-1 };
     //�؂�ւ�����
    const float visibleCoolTime = 1.0f;
    //�����Ă��邩�ǂ���
    bool isVisible = true;
    //�\���ؑփ^�C�}�[
    Timer* displaySwitchingTimer;
};