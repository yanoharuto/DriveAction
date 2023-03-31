#pragma once
#include "PlayerRelatedInfo.h"
#include "TimerUI.h"
#include "Utility.h"
#include "UIDataStruct.h"
#include "MiniMap.h"
#include "NumUI.h"
/// <summary>
/// �v���C���[�Ɋ֌W�̂���UI
/// </summary>
class PlayerRelatedUI final
{
public:
    PlayerRelatedUI(Timer* setTimer,int setFirstCoinNum);
    ~PlayerRelatedUI();
    /// <summary>
    /// �~�j�}�b�v�̍X�V�@��R�C���̖������X�V
    /// </summary>
    /// <param name="relatedInfo"></param>
    /// <param name="setCoinPosList"></param>
    void Update(PlayerRelatedInfo relatedInfo,std::list<VECTOR> setCoinPosList);
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();
private:
    //��������̉摜
    const std::string manualPass = "data/Manual.png";
    // /����̉摜�̃p�X
    const std::string slash = "data/slash.png";
    //�X���b�V��
    int slashHandle = -1;
    //�ŏ��̃R�C���̖���
    int firstCoinNum = 0;
    // �v���C���[��������������
    int nowGetCoinNum = 0;
    //�^�C�}�[
    TimerUI* timerUI;
    //�~�j�}�b�v
    MiniMap* minimapUI;
    //�R�C���̖�����`�悷��N���X
    NumUI* numUI;
    //���������UI���
    UIData manualData{ UI_SCREEN_WIDTH * 2,UI_SCREEN_HEIGHT * 10 ,-1};
    //�R�C���̖����ɂ��Ă�UI�̕`��ʒu
    float coinUIDrawX = UI_SCREEN_WIDTH * 15;
    //�R�C���̖����ɂ��Ă�UI�̕`��ʒu
    float coinUIDrawY = UI_SCREEN_HEIGHT * 8;
    //�t�H���g�摜�̃T�C�Y
    const float timerFontLoadSize = 80.0f;
    //�`��ʒu
    const float drawTimerX = UI_SCREEN_WIDTH * 17;
    //�`��ʒu
    const float drawTimerY = UI_SCREEN_HEIGHT * 4;
    //�t�H���g�̃T�C�Y
    const float fontSize = 1.0f;
};