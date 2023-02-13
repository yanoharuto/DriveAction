#pragma once
#include "CircuitDataStruct.h"
#include "SoundPlayer.h"
#include "ItemHolder.h"
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
    Racer(CircuitData circuitData);
    virtual ~Racer();
    /// <summary>
    /// �Ԃ𑖂点����A�C�e�����g�����肷��
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObj"></param>
    virtual void Update(float deltaTime,bool outsideHitFlag,DamageObjectGenerator* damageObj);
    /// <summary>
    /// ���̃��[�T�[�̎ԂɈ����̃I�u�W�F�N�g���Ԃ����Ă��邩���ׂ�
    /// </summary>
    /// <param name="objInfo"></param>
    /// <returns></returns>
    bool HitCheck(HitCheckExamineObjectInfo objInfo);
    /// <summary>
    /// �`�悷��
    /// </summary>
    void Draw();
    /// <summary>
    /// �Փˏ���
    /// </summary>
    /// <param name="conflictResultInfo"></param>
    /// <param name="deltaTime"></param>
    void ConflictProcces(ConflictExamineResultInfo conflictResultInfo,float deltaTime);
    /// <summary>
    /// �����蔻��𒲂ׂ邽�߂ɕK�v�ȏ��
    /// </summary>
    /// <returns></returns>
    HitCheckExamineObjectInfo GetCarHitCheckExamineInfo();
    /// <summary>
    /// ���������ꍇ�Ԃ����
    /// </summary>
    /// <returns></returns>
    ConflictExamineResultInfo GetConflictExamineResultInfo();
    /// <summary>
    /// �����N
    /// </summary>
    int* GetRankPointer();
    /// <summary>
    /// �`�F�b�N�|�C���g��Ԃ�
    /// </summary>
    CheckPoint* GetCheckPointer();
protected:
    /// <summary>
    /// ���ʏ���
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObj"></param>
    void CommonUpdate(float deltaTime, bool outsideHitFlag,DamageObjectGenerator* damageObj);
    /// <summary>
    /// �C���X�g���N�^�ŌĂ�
    /// </summary>
    /// <param name="car"></param>
    void SetCarPointer(Car* car);
    //����
    int rank;
    //�ʂ��Ă����`�F�b�N�|�C���g
    CheckPoint* checkPoint;
    //��
    Car* car;
    //��
    SoundPlayer* soundPlayer;
    //�A�C�e��������Ă��ĕۑ�����
    ItemHolder* itemHolder;
};

