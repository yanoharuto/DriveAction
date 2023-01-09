#include "LacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"
#include "StageSelect.h"
#include "StageDataAddressStruct.h"
#include "VECTOR3Loader.h"
#include "CourceDataLoader.h"
/// <summary>
/// ������
/// </summary>
/// <param name="lacerNum">�ԏ��̐��������X�g�ɒǉ������</param>
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
    for (int i = 0; i < static_cast<signed>(RacerList.max_size()); i++)
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
void RacerManager::Update(const float deltaTime, CircuitTrack* circuit)
{
    std::list<Racer>::iterator lacerIte;
    Racer lacer;
    for (lacerIte = RacerList.begin(); lacerIte != RacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        ArgumentConflictInfo conflictInfo;
        //�Ԃ̍X�V�@�R�[�X�O�ɏo�����ǂ����������Œ��ׂ�
        lacer.car->Update(deltaTime, circuit->GetOutsideHitFlag(lacer.car));
        //�`�F�b�N�|�C���g�̍X�V�̍X�V
        conflictInfo.SetObjInfo(true, lacer.car);
        //�Ԃ��`�F�b�N�|�C���g��ʉ߂��������ׂ�
        if (lacer.checkPoint->CheckPointUpdate(conflictInfo))
        {
            //�ԂɎ��̖ړI�n��`����
            conflictInfo.SetObjInfo(true, lacer.checkPoint);
            lacer.car->ConflictProcess(conflictInfo);
        }
        //�R�[�X�̕��Ƃ��ɂԂ����������ׂ�
        conflictInfo = circuit->GetCourceConflictInfo(lacer.car);
        if (conflictInfo.hitFlag)
        {
            //�Ԃ����Ă���Փˏ���
            lacer.car->ConflictProcess(conflictInfo);
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
    std::list<Racer>::iterator lacerIte;
    Racer lacer;
    for (lacerIte = RacerList.begin(); lacerIte != RacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        //car���g�Ɠ����蔻�����Ă���ʂ�Ȃ�
        if (lacer.car != obj)
        {
            //�������Ă邩���ׂ�@
            if (hitChecker.HitCheck(lacer.car, obj))
            {
                lacer.car->ConflictProcess(conflictInfo);
            }
        }
    }
}
/// <summary>
/// �ԏ�肽�����m�łԂ����ĂȂ������ׂ�
/// </summary>
void RacerManager::LacerConflictProcces()
{
    std::list<Racer>::iterator lacerIte;
    Racer lacer;
    for (lacerIte = RacerList.begin(); lacerIte != RacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        ArgumentConflictProcess(lacer.car);
    }
}

/// <summary>
  /// �`��
  /// </summary>
  /// <returns></returns>
void RacerManager::Draw()
{
    std::list<Racer>::iterator lacerIte;
    Racer lacer;
    for (lacerIte = RacerList.begin(); lacerIte != RacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        lacer.car->Draw();
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

