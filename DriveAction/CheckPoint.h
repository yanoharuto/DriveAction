#pragma once
#include <vector>
#include "ConflictExamineResultInfo.h"
#include "CircuitDataStruct.h"
#include "HitCheckExamineObjectInfo.h"
#include "Actor.h"
/// <summary>
/// �v���C���[������S�[��������������
/// </summary>
class CheckPoint final:
    public Actor
{
public:
    CheckPoint();

    /// <summary>
    /// �R�[�X��񕡐��p
    /// </summary>
    /// <param name="checkPointParam"></param>
    /// <returns></returns>
    CheckPoint(const CircuitData circuitData);
    //�f�X�g���N�^
    ~CheckPoint();
    /// <summary>
    /// �v���C���[���Ԃ������玟�̍s�����ݒ肷��
    /// </summary>
    /// <param name="carInfo">�Ԃ����������ׂ��</param>
    ConflictExamineResultInfo CheckPointUpdate(const HitCheckExamineObjectInfo carInfo);
    /// <summary>
    /// �`�F�b�N�|�C���g�ɎԂ��ʉ߂��������肷��
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="dir"></param>
    /// <param name="carPos"></param>
    /// <returns></returns>
    bool IsTransitCheckPointCar(VECTOR pos,VECTOR dir,VECTOR carPos);
    /// <summary>
    /// �S�[�������񐔂�Ԃ�
    /// </summary>
    /// <returns></returns>
    int GetGoalCount();
    //�`�F�b�N�|�C���g�ɒʉ߂����񐔂�Ԃ�
    int GetTransitCheckPointCount();
    /// <summary>
    /// �`�F�b�N�|�C���g�܂ł̍����o��
    /// </summary>
    /// <returns>�`�F�b�N�|�C���g�܂ł̍�</returns>
    float GetCheckPointDistance();
    bool HitCheckConflict(HitCheckExamineObjectInfo objInfo) override;
private:

    //�T�[�L�b�g�̃f�[�^
    CircuitData cPParam;
    //position���炱�ꂾ���߂�������S�[��
    const float goalTapeHalfLength = 70.0f;
    //���̃`�F�b�N�|�C���g�܂ł̌������o���n�߂�͈�
    const float goalRadius = 55.0f;
    //�Ԃ�Dir�Ɣ��Ό����Ȃ̂œ��ς������1�ɋ߂�������S�[����������
    const float dirJugeLine = 0.8f;
    //�`�F�b�N�|�C���g�̃x�N�^�[�𒲂ׂ��
    const int checkPointExamineCount = 4;
    //�ʉ߂�����
    int transitCheckPointCount = 0;
    //�S�[��������
    int goalCount = 0;
    //�x�N�^�[�z��̃T�C�Y
    int vecSize = 0;
    //�`�F�b�N�|�C���g�܂ł̍�
    float checkPointDistance;
};

