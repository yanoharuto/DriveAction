#pragma once
#include "Object.h"
#include "ArgumentConflictInfo.h"
#include "NeighborhoodInfo.h"
#include "CarNeighborhoodExamineInfo.h"
#include <string>

/// <summary>
/// �R�[�X
/// </summary>
class CircuitTrack final:
    public Object
{
public:
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="courceModelAdress"></param>
    /// <param name="outsideModelAdress"></param>
    /// <returns></returns>
    CircuitTrack(std::string courceModelAdress,std::string outsideModelAdress);
    CircuitTrack() {
        courceModelHandle = -1;
        outsideModelHandle = -1;
    };
    ///model���f���[�g
    ~CircuitTrack();
    /// <summary>
    /// �R�[�X�̊O���ɓ������Ă邩���ׂ�
    /// </summary>
    /// <param name="actor">�O���ɂ��邩���ׂ�������</param>
    /// <returns>�R�[�X�̊O���ɂ���Ȃ�True</returns>
    bool GetOutsideHitFlag(ConflictProccessArgumentInfo info) const;
    /// <summary>
    /// �R�[�X�̕ǂɂԂ����Ă邩���ׂ�
    /// </summary>
    /// <param name="Actor">�Ԃ����Ă邩���ׂ�������</param>
    /// <returns>�Ԃ����Ă���True</returns>
    ConflictProccessArgumentInfo GetCourceConflictInfo(ConflictProccessArgumentInfo info) const;

    NeighborhoodInfo GetOutsideExamineInfo(CarNeighborhoodExamineInfo examineInfo) const;
    /// <summary>
    /// �R�[�X�̃��f����`��
    /// </summary>
    void Draw();

private:
    ConflictProccessArgumentInfo GetSphereConflictModelInfo(int modelHandle,CarNeighborhoodExamineInfo examineInfo) const;
    //�R���W������Y�̕�����
    const int setupYDivNum = 8;
    //�R�[�X�̑傫��
    const float courceModelScaleValue = 0.15f;
    //�R�[�X�̊O���̑傫��
    const float outsideModelScaleValue = 0.15f;
    //�R�[�X�̈ʒu�T���Ɏg�������̎n�_
    const float sY = 0;
    //�R�[�X�̈ʒu�T���Ɏg�������̏I�_
    const float eY = -11;
    //�R�[�X�̐Ԕ��̓z
    const float gurdRadius = 2.0f;
    //�R�[�X��model
    int courceModelHandle;
    //�R�[�X�̊O����model
    int outsideModelHandle;
    //�R�[�X�̊O����model�̃|�W�V����
    const VECTOR outsideModelPosition = { 0,-8,0 };
};

