#pragma once

#include <string>

#include "UIManager.h"
class Timer;
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
    //���W���̃A�C�R��
    UIData collectIconData;
    //�Q�[���̖ڕW
    UIData gamePuroseData;

    int iconIncrement;
};