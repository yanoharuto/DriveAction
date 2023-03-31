#pragma once
#include "PlayerRelatedInfo.h"
#include "Timer.h"
/// <summary>
/// �ŏI�I�ȃX�R�A�̕ۑ���
/// </summary>
class ResultScore
{
public:
    /// <summary>
    /// �ŏI�I�ȃX�R�A�̕ۑ�
    /// </summary>
    ResultScore(Timer* timer,PlayerRelatedInfo playerInfo);
    ~ResultScore() {};
    /// <summary>
    /// �X�R�A�̏���
    /// </summary>
    /// <returns></returns>
    static int GetScore();
    /// <summary>
    /// �R�C����������X�R�A
    /// </summary>
    /// <returns></returns>
    static int GetCoinScore();
    /// <summary>
    /// ���������񐔕��w���X�R�A
    /// </summary>
    /// <returns></returns>
    static int GetHitScore();
    /// <summary>
    /// �c�莞�Ԃ̃X�R�A
    /// </summary>
    /// <returns></returns>
    static int GetTimeScore();
private:
    //�R�C���̃X�R�A
    static int coinScore;
    //�_���[�W���󂯂��񐔌���X�R�A
    static int hitScore;
    //�c�莞�ԃX�R�A
    static int timeScore;
    //�_���[�W����̂���I�u�W�F�N�g�ɐG�ꂽ��X�R�A����
    const int damageObjHitDec = 30;
    //�c�莞�Ԃ̃{�[�i�X
    const int timeBonus = 10;
    //��x��������Ȃ������ꍇ�̃X�R�A
    const int noHitScore = 500;
    //�R�C���̓{�[�i�X
    const int coinBonus = 500;
};

