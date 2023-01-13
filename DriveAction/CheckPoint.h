#pragma once
#include "Car.h"
#include <vector>
#include "ArgumentObjInfoStruct.h"
#include "CircuitDataStruct.h"
/// <summary>
/// �v���C���[������S�[��������������
/// </summary>
class CheckPoint final:
    public Object
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
    bool CheckPointUpdate(const ArgumentConflictInfo carInfo);
    /// <summary>
    /// ����CPU�ɂ��R�s�[�����邽�߂ɓn��
    /// </summary>
    /// <returns></returns>
    CircuitData GetCheckPoint() const;
    /// <summary>
    /// �S�[�������񐔂�Ԃ�
    /// </summary>
    /// <returns></returns>
    int GetGoalCount();
    int GetTransitCheckPointCount();
    /// <summary>
    /// �`�F�b�N�|�C���g�܂ł̍����o��
    /// </summary>
    /// <returns>�`�F�b�N�|�C���g�܂ł̍�</returns>
    float GetCheckPointDistance();
private:

    /// <summary>
    /// ����������
    /// </summary>
    void InitMember();
    //�T�[�L�b�g�̃f�[�^
    CircuitData cPParam;
    //position���炱�ꂾ���߂�������S�[��
    const float goalRadius = 100.0f;
    //�Ԃ�Dir�Ɣ��Ό����Ȃ̂œ��ς������1�ɋ߂�������S�[����������
    const float dirJugeLine = 0.8f;
    //�`�F�b�N�|�C���g�̃x�N�^�[�𒲂ׂ��
    const int vectorExamineCount = 5;
    //�ʉ߂�����
    int transitCheckPointCount = 0;
    //�S�[��������
    int goalCount = 0;
    //�x�N�^�[�z��̃T�C�Y
    int vecSize = 0;
    //�`�F�b�N�|�C���g�܂ł̍�
    float checkPointDistance;
};

