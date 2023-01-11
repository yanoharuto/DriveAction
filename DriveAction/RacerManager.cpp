#include "RacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"
#include "StageDataAddressStruct.h"
#include "CourceDataLoader.h"
#include <map>
/// <summary>
/// ������
/// </summary>
/// <param name="racerNum">�ԏ��̐��������X�g�ɒǉ������</param>
/// <returns></returns>
RacerManager::RacerManager(int cpuNum, CourceDataLoader* const courceDataLoader)
{
    //�v���C���[�̏���������
    CircuitData circuitData{ courceDataLoader->GetCheckPointPosList(),courceDataLoader->GetCheckPointDirList() };
    std::list<VECTOR> firstPosList = courceDataLoader->GetFirstPosList();
    std::list<VECTOR>::iterator firstPosIte = firstPosList.begin();
    Racer racer{};
    racer.rank = 0;
    racer.checkPoint = new CheckPoint(circuitData);
    racer.car = new Player(*firstPosIte,courceDataLoader->GetFirstDir());
    RacerList.push_back(racer);
    //���̎Ԃ̏���������
    ArgumentConflictInfo conflictInfo;
    for (int i = cpuNum; i > 0; i--)
    {
        firstPosIte++;
        racer.checkPoint = new CheckPoint(circuitData);
        racer.car = new CPUCar(*firstPosIte,courceDataLoader->GetFirstDir());
        racer.rank = 0;
        RacerList.push_back(racer);
        conflictInfo.SetObjInfo(false,racer.checkPoint);
        racer.car->ConflictProcess(conflictInfo);
    }
}
//�f�X�g���N�^
RacerManager::~RacerManager()
{
    for (int i = 0; i < static_cast<signed>(RacerList.size()); i++)
    {
        SAFE_DELETE(RacerList.front().car);
        SAFE_DELETE(RacerList.front().checkPoint);
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
    for (racerIte = RacerList.begin(); racerIte != RacerList.end(); racerIte++)
    {
        racer = *racerIte;
        ArgumentConflictInfo conflictInfo;
        //�Ԃ̍X�V�@�R�[�X�O�ɏo�����ǂ����������Œ��ׂ�
        racer.car->Update(deltaTime, circuit->GetOutsideHitFlag(racer.car));
        //�`�F�b�N�|�C���g�̍X�V�̍X�V
        conflictInfo.SetObjInfo(true, racer.car);
        //�Ԃ��`�F�b�N�|�C���g��ʉ߂��������ׂ�
        if (racer.checkPoint->CheckPointUpdate(conflictInfo))
        {
            //�ԂɎ��̖ړI�n��`����
            conflictInfo.SetObjInfo(true, racer.checkPoint);
            racer.car->ConflictProcess(conflictInfo);
        }
        //�R�[�X�̕��Ƃ��ɂԂ����������ׂ�
        conflictInfo = circuit->GetCourceConflictInfo(racer.car);
        if (conflictInfo.hitFlag)
        {
            //�Ԃ����Ă���Փˏ���
            racer.car->ConflictProcess(conflictInfo);
        }
    }
}
/// <summary>
/// �����̕��̂ɂԂ����������ׂ�
/// </summary>
/// <param name="obj">���ׂ�������</param>
void RacerManager::ArgumentConflictProcess(Object* obj)
{
    ArgumentConflictInfo conflictInfo;
    conflictInfo.SetObjInfo(false,obj);
    std::list<Racer>::iterator racerIte;
    Racer racer;
    for (racerIte = RacerList.begin(); racerIte != RacerList.end(); racerIte++)
    {
        racer = *racerIte;
        //car���g�Ɠ����蔻�����Ă���ʂ�Ȃ�
        if (racer.car != obj)
        {
            //�������Ă邩���ׂ�@
            if (hitChecker.HitCheck(racer.car, obj))
            {
                racer.car->ConflictProcess(conflictInfo);
            }
        }
    }
}
void RacerManager::RacerRankUpdate()
{

}
/// <summary>
/// �ԏ�肽�����m�łԂ����ĂȂ������ׂ�
/// </summary>
void RacerManager::RacerConflictProcces()
{
    std::list<Racer>::iterator racerIte;
    Racer racer;
    for (racerIte = RacerList.begin(); racerIte != RacerList.end(); racerIte++)
    {
        racer = *racerIte;
        ArgumentConflictProcess(racer.car);
    }
}
/// <summary>
/// �v���C���[�̃S�[�������񐔂�Ԃ�
/// </summary>
/// <returns></returns>
int RacerManager::GetPlayerGoalCount()
{
    return RacerList.front().checkPoint->GetGoalCount();
}

int RacerManager::GetPlayerRank()
{
    return RacerList.front().rank;
}

/// <summary>
  /// �`��
  /// </summary>
  /// <returns></returns>
void RacerManager::Draw()
{
    std::list<Racer>::iterator racerIte;
    Racer racer;
    for (racerIte = RacerList.begin(); racerIte != RacerList.end(); racerIte++)
    {
        racer = *racerIte;
        racer.car->Draw();
    }
}
/// <summary>
/// ��ԍŏ��ɒǉ������I�u�W�F�N�g��Ԃ�
/// </summary>
/// <returns></returns>
Object* RacerManager::GetPlayer() const
{
    return RacerList.front().car;
}

