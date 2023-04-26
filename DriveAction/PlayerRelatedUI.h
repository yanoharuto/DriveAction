#pragma once
#include <list>
#include "PlayerRelatedInfo.h"
#include "Utility.h"
#include "UIManager.h"
class MiniMap;
class TimerUI;
class Timer;
class NumUI;
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
    UIData manualData;
    //�X���b�V��
    UIData slashHandle;
    //���������R�C���̖����ɂ��Ă�UI�̕`��ʒu
    int coinUIDrawX = UI_SCREEN_WIDTH * 15;
    //���������R�C���̖����ɂ��Ă�UI�̕`��ʒu
    int coinUIDrawY = static_cast<int>(UI_SCREEN_HEIGHT * 8);
    
    //�t�H���g�̃T�C�Y
    const int fontSize = 1;
};