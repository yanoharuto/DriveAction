#pragma once
#include "CircuitDataStruct.h"
#include "SoundPlayer.h"
#include "Car.h"
#include "CheckPoint.h"
#include "ConflictExamineResultInfo.h"
#include "DamageObjectGenerator.h"
/// <summary>
/// ���[�T�[�@����@�R���s���[�^�[�ƃv���C���[�̓���
/// </summary>
class Racer abstract
{
public:
    Racer();
    virtual ~Racer();
    /// <summary>
    /// �Ԃ𑖂点����A�C�e�����g�����肷��
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObj"></param>
    virtual void Update();
    /// <summary>
    /// �`�悷��
    /// </summary>
    void Draw();
    /// <summary>
    /// ���i�O�ɏ㉺�ɓ���
    /// </summary>
    void UpDown();
    /// <summary>
    /// �����N
    /// </summary>
    int* GetRankPointer();
    /// <summary>
    /// �`�F�b�N�|�C���g��Ԃ�
    /// </summary>
    CheckPoint* GetCheckPointer();

protected:

    int transitCPCount = 0;

    bool reverse = false;
    //����
    int rank;
    //�ʂ��Ă����`�F�b�N�|�C���g
    CheckPoint* checkPoint;
    //��
    Car* car;
};

