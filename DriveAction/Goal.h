#pragma once
#include "Stage.h"
#include <vector>
/// <summary>
/// �v���C���[������S�[��������������
/// </summary>
class Goal :
    public Stage
{
public:
    Goal(const int roundNum);
    ~Goal();
    /// <summary>
    /// �v���C���[���Ԃ������玟�̍s�����ݒ肷��
    /// </summary>
    /// <param name="actor"></param>
    void ConflictProcess(Actor* actor)override;
private:
    //�Ԃ����ɍs���ׂ��s���悪�����Ă���
    std::vector<VECTOR> positionVec;
    //�t�����ăS�[�����Ȃ��悤�ɕ������悹��
    std::vector<VECTOR> directionVec;
    //position���炱�ꂾ���߂�������S�[��
    const float goalRadius = 80.0f;
    //�Ԃ�Dir�Ɣ��Ό����Ȃ̂œ��ς������1�ɋ߂�������S�[����������
    const float dirJugeLine = 0.8f;
    //�S�[�����ꂽ��
    int goalNum = 0;
    //�x�N�^�[�z��̃T�C�Y
    int vecSize = 0;
    //���T������S�[���Ȃ̂�
    int goalRoundNum = 0;
    //directionVec���������f�[�^������
    VECTOR direction;
};

