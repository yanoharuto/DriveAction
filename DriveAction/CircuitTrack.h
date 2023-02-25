#pragma once
#include <string>
#include "Actor.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "NeighborhoodInfo.h"
#include "CarNeighborhoodExamineInfo.h"
#define  COURCE_GENERATE_NUM 5
struct StageModel;
/// <summary>
/// �R�[�X
/// </summary>
class CircuitTrack final:
    public Actor
{
public:
    /// <summary>
    /// ������
    /// </summary>
    CircuitTrack();
    ///model���f���[�g
    ~CircuitTrack();
    /// <summary>
    /// �R�[�X�̊O���ɓ������Ă邩���ׂ�
    /// </summary>
    /// <param name="actor">�O���ɂ��邩���ׂ�������</param>
    /// <returns>�R�[�X�̊O���ɂ���Ȃ�True</returns>
    bool GetOutsideHitFlag(HitCheckExamineObjectInfo info) const;

    bool HitCheckConflict(const HitCheckExamineObjectInfo examineObjInfo);
    /// <summary>
    /// �R�[�X�̕ǂɂԂ����Ă邩���ׂ�
    /// </summary>
    /// <param name="Actor">�Ԃ����Ă邩���ׂ�������</param>
    /// <returns>�Ԃ����Ă���True</returns>
    ConflictExamineResultInfo GetCourceConflictInfo(HitCheckExamineObjectInfo info) const;
    /// <summary>
    /// �R�[�X�̃��f����`��
    /// </summary>
    void Draw();
    void Update(VECTOR playerPos);
private:
   
    ConflictExamineResultInfo GetSphereConflictModelInfo(int modelHandle,HitCheckExamineObjectInfo examineInfo) const;
   
    //���ɐ�������X�e�[�W�̈ʒu
    VECTOR nextGeneratePos = {};
    //�ŏ��̃|�W�V�����̈ʒu
    const VECTOR firstPos = { -150.0f,0.0f,0.0f };
    //�R���W������Y�̕�����
    const int setupYDivNum = 8;
    //�R�[�X�̑傫��
    const float modelScaleHandle = 0.35f;
    //�͂����Ԃ���
    const float setBouncePower = 1.0f;
    //�R�[�X�̐Ԕ��̓z�̑傫��
    const float gurdRadius = 3.5f;

    //�R�[�X�̊O����model�̃|�W�V����
    const VECTOR outsideModelPosition = { 0,-8,0 };
    //�X�e�[�W��model�̃t�@�C���̃p�X
    const std::string stageFilePass = "Stage/";
    const std::string courceFilePass = "Obstracle.mv1";
    const std::string obstracleFilePass = "Rail.mv1";
    const std::string floorFilePass = "Floor.mv1";
    //�R�[�X�̃��f���̐�
    const int courceModelNum = 2;
    //�R�[�X�̃p�^�[���̐�
    const int courcePatternNum = 3;
    //���ɏo��model�̃G�C���A�X
    int random = 1;
    int obstracleModelHandle;
    int courceModelHandle;
    int floorModelHandle;
};