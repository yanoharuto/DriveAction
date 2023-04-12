#pragma once
#include <string>
#include <vector>
#include "Rock.h"
#include "StageWall.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "SphereCollider.h"

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

    //�R�[�X�̊O����model�̃|�W�V����
    const float rockYPos = 20;
    //�X�e�[�W��model�̃t�@�C���̃p�X
    const std::string stageFilePass = "Stage/";
    
    //�n��
    const std::string floorFilePass = "Floor.mv1";

    //���ɏo��model�̃G�C���A�X
    int random = 1;
    //�n��
    int floorModelHandle;
    std::vector<Rock*> rocks;
    StageWall* stageWall;
};