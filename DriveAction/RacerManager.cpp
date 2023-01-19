#include "RacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"
#include "StageDataAddressStruct.h"
#include "CourceDataLoader.h"
#include <algorithm>
/// <summary>
/// ������
/// </summary>
/// <param name="racerNum">�ԏ��̐��������X�g�ɒǉ������</param>
/// <returns></returns>
RacerManager::RacerManager(int cpuNum, CourceDataLoader* const courceDataLoader)
{
    //�R�[�X�̏��Ƃ�������������炤
    CircuitData circuitData{ courceDataLoader->GetCheckPointPosList(),courceDataLoader->GetCheckPointDirList() };
    std::list<VECTOR> firstPosList = courceDataLoader->GetFirstPosList();
    std::list<VECTOR>::iterator firstPosIte = firstPosList.begin();
    //�v���C���[�̏���������
    Racer racer{};

    racer.rank = 0;
    racer.checkPoint = new CheckPoint(circuitData);

    racer.car = new Player(*firstPosIte,courceDataLoader->GetFirstDir());
    racerList.push_front(racer); 
    RacerRankInfo rankInfo{};
    Racer* racerP;
    racerP = &racerList.front();
    rankInfo.checkPoint = racerP->checkPoint;
    rankInfo.rank = &racerP->rank;
    player = &racerList.front();

    racerRankList.push_back(rankInfo);
    //���̎Ԃ̏���������
    ArgumentConflictInfo conflictInfo;
    for (int i = cpuNum; i > 0; i--)
    {
        firstPosIte++;
        racer.checkPoint = new CheckPoint(circuitData);
        rankInfo.checkPoint = racer.checkPoint;
        racer.car = new CPUCar(*firstPosIte,courceDataLoader->GetFirstDir());
        racer.rank = 0;
        racerList.push_front(racer);

        racerP = &racerList.front();
        rankInfo.checkPoint = racerP->checkPoint;
        rankInfo.rank = &racerP->rank;
        racerRankList.push_back(rankInfo);
        
    }
}
//�f�X�g���N�^
RacerManager::~RacerManager()
{
    for (int i = 0; i < static_cast<signed>(racerList.size()); i++)
    {
        SAFE_DELETE(racerList.front().car);
        SAFE_DELETE(racerList.front().checkPoint);
    }
}
/// <summary>
/// �ԏ�肽���̍X�V
/// </summary>
/// <param name="deltaTime">�t���[���Ԃ̌o�ߎ���</param>
/// <param name="circuit">����R�[�X</param>
void RacerManager::RacerUpdate(const float deltaTime, CircuitTrack* circuit)
{
    std::list<Racer>::iterator racerIte;
    Racer racer;
    bool hitFlag;
    NeighborhoodInfo neighInfo;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        ArgumentConflictInfo conflictInfo;
        conflictInfo.SetObjInfo(false,racer.car);
        //����ɉ������邩���ׂ�
        hitFlag = circuit->GetOutsideHitFlag(conflictInfo);
        neighInfo = circuit->GetObjNeighbornhoodInfo(racer.car->GetNeighExamineInfo());
        //�Ԃ̍X�V�@
        racer.car->Update(deltaTime, hitFlag,neighInfo);
        //�`�F�b�N�|�C���g�̍X�V�̍X�V
        conflictInfo.SetObjInfo(true, racer.car);
        //�Ԃ��`�F�b�N�|�C���g��ʉ߂��������ׂ�
        racer.checkPoint->CheckPointUpdate(conflictInfo);
        //�ԂɎ��̖ړI�n��`����
        conflictInfo.SetObjInfo(true, racer.checkPoint);
        racer.car->ConflictProcess(deltaTime, conflictInfo);
        //�R�[�X�̕��Ƃ��ɂԂ����������ׂ�
        conflictInfo.SetObjInfo(false, racer.car);
        conflictInfo = circuit->GetCourceConflictInfo(conflictInfo);
        if (conflictInfo.hitFlag)            //�Ԃ����Ă���Փˏ���
        {
            racer.car->ConflictProcess(deltaTime, conflictInfo);
        }
    }
}
/// <summary>
/// �����̕��̂ɂԂ����������ׂ�
/// </summary>
/// <param name="obj">���ׂ�������</param>
void RacerManager::ArgumentConflictProcess(float deltaTime,Object* obj)
{
    ArgumentConflictInfo conflictInfo;
    conflictInfo.SetObjInfo(false,obj);
    std::list<Racer>::iterator racerIte;
    Racer racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        //car���g�Ɠ����蔻�����Ă���ʂ�Ȃ�
        if (racer.car != obj)
        {
            //�������Ă邩���ׂ�@
            if (hitChecker.HitCheck(racer.car, obj))
            {
                racer.car->ConflictProcess(deltaTime,conflictInfo);
            }
        }
    }
}
void RacerManager::RacerRankUpdate()
{
    std::list<RacerRankInfo>::iterator rankIte;
    RacerRankInfo rankInfo;
    int transitCheckCount = 0;
    int maxTransitCheckCount = 0;
    for (rankIte = racerRankList.begin(); rankIte != racerRankList.end(); rankIte++)
    {
        rankInfo = *rankIte;
        transitCheckCount = rankInfo.checkPoint->GetTransitCheckPointCount();
        if (transitCheckCount > maxTransitCheckCount)
        {
            std::swap(*racerRankList.begin(), rankInfo);
        }
    }
    int rank = 1;
    for (rankIte = racerRankList.begin(); rankIte != racerRankList.end(); rankIte++)
    {
        rankInfo = *rankIte;
        *rankInfo.rank = rank;
        rank++;
    }
    player;
}
/// <summary>
/// �ԏ�肽�����m�łԂ����ĂȂ������ׂ�
/// </summary>
void RacerManager::RacerConflictProcces(float deltaTime)
{
    std::list<Racer>::iterator racerIte;
    Racer racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        ArgumentConflictProcess(deltaTime,racer.car);
    }
}
/// <summary>
/// �v���C���[�̃S�[�������񐔂�Ԃ�
/// </summary>
/// <returns></returns>
int RacerManager::GetPlayerGoalCount()
{
    return player->checkPoint->GetGoalCount();
}

int RacerManager::GetPlayerRank()
{
    return player->rank;
}

/// <summary>
  /// �`��
  /// </summary>
  /// <returns></returns>
void RacerManager::Draw()
{
    std::list<Racer>::iterator racerIte;
    Racer racer;
    for (racerIte = racerList.begin(); racerIte != racerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer.car->Draw();
    }
}
/// <summary>
/// ��ԍŏ��ɒǉ������I�u�W�F�N�g��Ԃ�
/// </summary>
/// <returns></returns>
Object* RacerManager::GetPlayerCar() const
{
    Car* playerCar= player->car;
    return playerCar;
}

