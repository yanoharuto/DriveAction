#pragma once
#include <string>
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "MeshCollider.h"

#define  COURCE_GENERATE_NUM 5
struct StageModel;
/// <summary>
/// �R�[�X
/// </summary>
class CircuitTrack final
{
public:
    /// <summary>
    /// ������
    /// </summary>
    CircuitTrack();
    ///model���f���[�g
    ~CircuitTrack();
    /// <summary>
    /// �R�[�X�̃��f����`��
    /// </summary>
    void Draw();
private:
    ConflictExamineResultInfo resultInfo = { false,ObjectTag::stage,{},{},0.0f,15.0f };
    //�R�[�X�̑傫��
    const float modelScaleHandle = 0.35f;
    
    //��Q���̕�
    const float setRadius = 3.5f;

    //�R�[�X�̊O����model�̃|�W�V����
    const VECTOR outsideModelPosition = { 0,-200,0 };
    //�X�e�[�W��model�̃t�@�C���̃p�X
    const std::string stageFilePass = "Stage/";
    //���[��
    const std::string courceFilePass = "Rail.mv1";
    //��Q��
    const std::string obstracleFilePass = "Obstracle.mv1";
    //�n��
    const std::string floorFilePass = "Floor.mv1";
    //�R�[�X�̃��f���̐�
    const int courceModelNum = 2;
    //�R�[�X�̃p�^�[���̐�
    const int courcePatternNum = 3;
    //���ɏo��model�̃G�C���A�X
    int random = 1;
    
    //��Q�����f���n���h��
    int obstracleModelHandle;
    //�R�[�X
    int courceModelHandle;
    //�n��
    int floorModelHandle;
    MeshCollider* obstracleCollider;
    MeshCollider* courceCollider;
    MeshCollider* floorCollider;
};