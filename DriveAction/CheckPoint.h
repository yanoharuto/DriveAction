#pragma once
#include <vector>
#include "ConflictExamineResultInfo.h"

#include "HitCheckExamineObjectInfo.h"
#include "Actor.h"
/// <summary>
/// �v���C���[������S�[��������������
/// </summary>
class CheckPoint final
{
public:
    CheckPoint();
    //�f�X�g���N�^
    ~CheckPoint();
    /// <summary>
    /// �`�F�b�N�|�C���g��ʉ߂��������ׂ�
    /// </summary>
    /// <param name="carInfo">�Ԃ����������ׂ��</param>
    bool IsTransitCheckPoint(int transitCount, const HitCheckExamineObjectInfo carInfo);
    /// <summary>
    /// �`�F�b�N�|�C���g�܂ł̍����o��
    /// </summary>
    /// <returns>�`�F�b�N�|�C���g�܂ł̍�</returns>
    float GetCheckPointDistance(int transitCount,VECTOR objPos);
    /// <summary>
    /// �ʉ߉񐔂͉���S�[���������ƂȂ̂��Ԃ�
    /// </summary>
    /// <param name="transitCount"></param>
    /// <returns></returns>
    int GetGoalCount(int transitCount);
    VECTOR GetCheckPointPos(int transitCount);
    VECTOR GetCheckPointDir(int transitCount);
private:
    /// <summary>
/// �`�F�b�N�|�C���g�ɎԂ��ʉ߂��������肷��
/// </summary>
/// <param name="pos"></param>
/// <param name="dir"></param>
/// <param name="carPos"></param>
/// <returns></returns>
    bool IsTransitCheckPointCar(VECTOR pos, VECTOR dir, VECTOR carPos);

    //�x�N�^�[�z��̃T�C�Y
    int vecSize = 0;
    //�S�[���܂ł̓��̂�e�L�X�g
    const std::string checkPointPosPass = "/CourcePos.txt";
    //�S�[���܂ł̓��̂�e�L�X�g
    const std::string checkPointDirPass = "/CourceDir.txt";
};

