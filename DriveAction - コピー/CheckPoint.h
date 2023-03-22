#pragma once
#include <vector>
#include "ConflictExamineResultInfo.h"

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
    VECTOR GetLastPos();
    VECTOR GetLastDir();

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
    //�ʉ߂�����
    int transitCount = 0;
    //�S�[��������
    int goalCount = 0;
    //�x�N�^�[�z��̃T�C�Y
    int vecSize = 0;
    //�`�F�b�N�|�C���g�܂ł̍�
    float checkPointDistance;
};

