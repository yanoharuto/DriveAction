#pragma once
#include <string>
#include "Utility.h"
#include "Timer.h"
#include "DxLib.h"
#include "SwitchUI.h"
#include "StringUI.h"
#include "PlayerRelatedInfo.h"
#include "NumUI.h"
#include "ResultScore.h"
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
    ~PostGoalStaging();
    bool Update();
    void Draw();
private:
    struct ScoreUI
    {
        UIData data;
        int score;
    };

    float x = 0.0f;
    float y = 0.0f;
    //�I���A�i�E���X
    int spaceClickCount = 0;

    //�Ō�̏u�Ԃ̉摜
    int screenGraph = -1;
    //�A�i�E���X�̈ړ���
    const float goalMoveX = 10.0f;
    //�X�y�[�X�L�[����������
    const float spaceKeyCoolTime = 1.5f;
    //�X�R�A�̎�ނ̑傫��
    const float scoreSize = 0.7f;

    //�����̑傫��
    const float numSize = 1.3f;
    //�I���̃A�i�E���X�̐F
    unsigned int goalMarkerUIColor = GetColor(200, 100, 100);
    //�X�y�[�X�L�[�Ñ�
    SwitchUI* switchUI;
    //�I���̃A�i�E���X
    StringUI* stringUI;
    ScoreUI scoreUI[SCORE_KIND_NUM];
    //�X�R�A�̕`��W
    NumUI* num;
    Timer* timer;
    int numDrawX = UI_SCREEN_WIDTH * 14.0f;
    const std::string clapSE = "clap.mp3";
    const std::string rouretteSE = "rourette.mp3";
    const std::string stopSE = "stopRourette.mp3";
};

