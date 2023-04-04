#pragma once
#include "PlayerRelatedInfo.h"
#include "Timer.h"
#define SCORE_KIND_NUM 4

/// <summary>
/// �ŏI�I�ȃX�R�A�̕ۑ���
/// </summary>
class ResultScore
{
public:
    enum ScoreKind
    {
        time = 0,
        hit = 1,
        collect = 2,
        total = 3
    };
    /// <summary>
    /// �ŏI�I�ȃX�R�A�̕ۑ�
    /// </summary>
    ResultScore(Timer* timer,PlayerRelatedInfo playerInfo);
    ~ResultScore() {};
    /// <summary>
    /// �X�R�A�̏���
    /// </summary>
    /// <returns></returns>
    static int GetScore(ScoreKind);
    static int GetScore(int kindNum);
    /// <summary>
    /// �R�C����������X�R�A
    /// </summary>
    /// <returns></returns>
    static int GetCollectBonus();
    /// <summary>
    /// ���������񐔕��w���X�R�A
    /// </summary>
    /// <returns></returns>
    static int GetHitBunus();
    /// <summary>
    /// �c�莞�Ԃ̃X�R�A
    /// </summary>
    /// <returns></returns>
    static int GetTimeBunus();
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

