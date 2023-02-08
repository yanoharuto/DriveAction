#pragma once
#include <List>
#include <string>
#include "PlaySceneCamaeraArgumentInfo.h"
#include "ConflictProcesser.h"
#include "HitChecker.h"
#include "SoundPlayer.h"
#include "ItemHolder.h"
#include "Racer.h"
#include "Player.h"
class CourceDataLoader;
class CircuitTrack;

struct ConflictExamineResultInfo;
struct PlayerRelatedInfo;

/// <summary>
/// ���[�T�[�̏��ʑ���Ɏg��
/// </summary>
struct RacerRankInfo
{
    int* rankP;
    CheckPoint* checkPointP;
};
/// <summary>
/// �ԏ��̃}�l�[�W���[
/// </summary>
class RacerManager
{
public:
    RacerManager() {};
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="lacerNum">�ԏ��̐��������X�g�ɒǉ������</param>
    /// <returns></returns>
    RacerManager(int cpuNum, CourceDataLoader* const courceDataLoader);
    //�f�X�g���N�^
    ~RacerManager();
    /// <summary>
    /// �ԏ�肽���̍X�V
    /// </summary>
    /// <param name="deltaTime">�t���[���Ԃ̌o�ߎ���</param>
    /// <param name="circuit">����R�[�X</param>
    void RacerUpdate(const float deltaTime, CircuitTrack* circuit, FiringItemManager* firingItemManager);
    /// <summary>
    /// �����̕��̂ɂԂ����������ׂ�
    /// </summary>
    /// <param name="obj"></param>
    void ArgumentConflictProcess(float deltaTime,Racer* obj);
    /// <summary>
    /// ���[�T�[�����̏��ʂ̍X�V
    /// </summary>
    void RacerRankUpdate();
    /// <summary>
    /// �`��
    /// </summary>
    /// <returns></returns>
    void Draw();
    /// <summary>
    /// ��ԍŏ��ɒǉ������I�u�W�F�N�g��Ԃ�
    /// </summary>
    /// <returns></returns>
    PlaySceneCameraArgumentInfo GetPlayerCarPosDir();
    /// <summary>
    /// �ԏ�肽�����m�łԂ����ĂȂ������ׂ�
    /// </summary>
    void RacerConflictProcces(ConflictProcesser* conflictProcesser, CircuitTrack* circuit, float deltaTime);
    /// <summary>
    /// �v���C���[�̃S�[�������񐔂�Ԃ�
    /// </summary>
    /// <returns></returns>
    int GetPlayerGoalCount();

    /// <summary>
    /// �v���C���[�̏���n��
    /// </summary>
    /// <returns></returns>
    PlayerRelatedInfo GetPlayerRelatedInfo();
private:
    //���[�T�[�̍ő�l��
    static const int maxRacerNum = 6;
    //���[�T�[�̐�
    int racerNum = 0;
    //���[�T�[�̔z��@
   
    //racerInstanceArray���w���Ă��郊�X�g
    std::list<Racer*> racerList;
    //���[�T�[�̏��ʂ��X�V���邽�߂ɕK�v�ȃ��X�g
    std::list<RacerRankInfo> racerRankList;
    //�������Ă邩�ǂ������ׂ�
    HitChecker hitChecker;
    //�v���C���[�̏��
    Player* player;
};