#pragma once
#include <string>
#include "Utility.h"
#include "UIManager.h"
#include "DxLib.h"
#include "SwitchUI.h"
#include "StringUI.h"
#include "PlayerRelatedInfo.h"
#include "NumUI.h"
/// <summary>
/// �S�[����̉��o������
/// </summary>
class PostGoalStaging
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
    float x = 0.0f;
    float y = 0.0f;
    //�A�i�E���X�̈ړ���
    const float goalMoveX = 10.0f;
    //�I���A�i�E���X
    bool isEndGoalUI = false;

    //�Ō�̏u�Ԃ̉摜
    int screenGraph = -1;
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
    //���������񐔂̃X�R�A
    UIData hitUI;
    //���Ԃ̃X�R�A
    UIData timeUI;
    //�X�R�A�̍��v
    UIData scoreUI;
    //�R�C���̃X�R�A
    UIData coinUI;
    //�X�R�A�̕`��W
    NumUI* num;
    int numDrawX = UI_SCREEN_WIDTH * 14.0f;
    const std::string clapSE = "clap.mp3";
};

