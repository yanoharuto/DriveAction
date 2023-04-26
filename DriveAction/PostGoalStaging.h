#pragma once
#include <string>
#include "Utility.h"
#include "DxLib.h"
#include "UIManager.h"
#include "ResultScore.h"
class NumUI;
class SwitchUI;
class Timer;
struct PlayerRelatedInfo;
/// <summary>
/// �S�[����̉��o������
/// </summary>
class PostGoalStaging final
{
public:
    /// <summary>
    /// �S�[����̉��o������
    /// </summary>
    PostGoalStaging();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PostGoalStaging();
    /// <summary>
    /// �X�R�A�����X�ɓn��
    /// </summary>
    /// <returns></returns>
    bool Update();
    /// <summary>
    /// �X�R�A�̕`��
    /// </summary>
    void Draw();
private:
    /// <summary>
    /// �X�R�A�̕\��
    /// </summary>
    struct ScoreUI
    {
        UIData data;
        int score;
    };
    //�I���A�i�E���X
    int spaceClickCount = 0;

    //�Ō�̏u�Ԃ̉摜
    int screenGraph = -1;
    //�A�i�E���X�̈ړ���
    const float goalMoveX = 10.0f;
    //�X�y�[�X�L�[����������
    const float spaceKeyCoolTime = 1.5f;

    //�����̑傫��
    const float numSize = 1.3f;
    //�I���̃A�i�E���X�̐F
    unsigned int goalMarkerUIColor = GetColor(200, 100, 100);
    //�X�y�[�X�L�[�Ñ�
    SwitchUI* switchUI;
    //�e�X�R�A��\�����邽�߂̔z��
    ScoreUI scoreUI[SCORE_KIND_NUM];
    //�S�[�������Ƃ��̏I���A�i�E���X
    //�X�R�A�̕`��W
    NumUI* num;
    //�^�C�}�[
    Timer* timer;
    //�X�R�A�̐�����\������Ƃ���X���W
    int numDrawX = UI_SCREEN_WIDTH * 15;
    //�Q�[���I�����̉�
    const std::string clapSE = "clap.mp3";
    //�X�R�A��\������Ƃ��̉�
    const std::string rouretteSE = "rourette.mp3";
    //�X�R�A��\�����I��������̉�
    const std::string stopSE = "stopRourette.mp3";
    //���̏����ɍs�����̉�
    const std::string nextSE = "Sys_Set02-pop down.mp3";
};