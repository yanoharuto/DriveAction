#pragma once
#include <List>
#include <string>
#include "ConflictProcesser.h"
#include "HitChecker.h"
class CourceDataLoader;
class Object;
class CheckPoint;
class Car;
class CircuitTrack;
/// <summary>
/// �����蔻��Ŏg���n���Ăق������
/// Actor�ɒ�`
/// </summary>
struct ConflictExamineResultInfo;
struct PlayerRelatedInfo;
/// <summary>
/// �����Ă�Ԃ̏��
/// </summary>
struct Racer
{
    int rank;
    CheckPoint* checkPoint;
    Car* car;
};
struct PlayerRacer
{
    int* rank;
    CheckPoint* checkPoint;
    Car* car;
};
/// <summary>
/// 
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
    void RacerUpdate(ConflictProcesser* conflictProcesser,const float deltaTime, CircuitTrack* circuit);
    /// <summary>
    /// �����̕��̂ɂԂ����������ׂ�
    /// </summary>
    /// <param name="obj"></param>
    void ArgumentConflictProcess(float deltaTime,Object* obj);
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
    Object* GetPlayerCar() const;
    /// <summary>
    /// �ԏ�肽�����m�łԂ����ĂȂ������ׂ�
    /// </summary>
    void RacerConflictProcces(float deltaTime);
    /// <summary>
    /// �v���C���[�̃S�[�������񐔂�Ԃ�
    /// </summary>
    /// <returns></returns>
    int GetPlayerGoalCount();
    /// <summary>
    /// �v���C���[�̃����N��\��
    /// </summary>
    /// <returns></returns>
    int GetPlayerRank();
    PlayerRelatedInfo GetPlayerRelatedInfo();
private:
    static const int maxRacerNum = 6;
    int racerNum = 0;
    Racer racerInstanceArray[maxRacerNum];
    //�ԏ��B�̃��X�g
    std::list<Racer*> racerList;
    std::list<RacerRankInfo> racerRankList;
    //�������Ă邩�ǂ������ׂ�
    HitChecker hitChecker;
    PlayerRacer player;
};