#include "LacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"
#include "StageSelect.h"
#include "StageDataAddressStruct.h"
#include "VECTOR3Loader.h"
/// <summary>
/// ������
/// </summary>
/// <param name="lacerNum">�ԏ��̐��������X�g�ɒǉ������</param>
/// <returns></returns>
LacerManager::LacerManager(int cpuNum,std::string chekPointAddress)
{
    //�v���C���[�̏���������
    Lacer lacer{};
    lacer.rank = 0;
    lacer.checkPoint = new CheckPoint(chekPointAddress.c_str());
    lacer.car = new Player();
    lacerList.push_back(lacer);
    //���̎Ԃ̏���������
    ArgumentConflictInfo conflictInfo;
    for (int i = cpuNum; i > 0; i--)
    {
        lacer.checkPoint = new CheckPoint(lacerList.front().checkPoint->GetCheckPoint());
        lacer.car = new CPUCar( );
        lacer.rank = 0;
        lacerList.push_back(lacer);
        conflictInfo.SetObjInfo(false,lacer.checkPoint);
        lacer.car->ConflictProcess(conflictInfo);
    }
}
//�f�X�g���N�^
LacerManager::~LacerManager()
{
    for (int i = 0; i < static_cast<signed>(lacerList.max_size()); i++)
    {
        SAFE_DELETE(lacerList.front().car);
        SAFE_DELETE(lacerList.front().checkPoint);
    }
}
/// <summary>
/// �ԏ�肽���̍X�V
/// </summary>
/// <param name="deltaTime">�t���[���Ԃ̌o�ߎ���</param>
/// <param name="circuit">����R�[�X</param>
void LacerManager::Update(const float deltaTime,CircuitTrack* circuit)
{
    void(LacerManager::*function)(Lacer, float, CircuitTrack*);
    function = &LacerManager::LacerUpdateProcces;
    LacerLoop(function,deltaTime,circuit);
}
/// <summary>
/// �����̕��̂ɂԂ����������ׂ�
/// </summary>
/// <param name="obj">���ׂ�������</param>
void LacerManager::ArgumentConflictProcess(Object* obj)
{
    ArgumentConflictInfo conflictInfo;
    conflictInfo.SetObjInfo(false,obj);
    std::list<Lacer>::iterator lacerIte;
    Lacer lacer;
    for (lacerIte = lacerList.begin(); lacerIte != lacerList.end(); lacerIte++)
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
void LacerManager::LacerConflictProcces()
{
    std::list<Lacer>::iterator lacerIte;
    Lacer lacer;
    for (lacerIte = lacerList.begin(); lacerIte != lacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        ArgumentConflictProcess(lacer.car);
    }
}

void LacerManager::LacerUpdateProcces(Lacer lacer, float deltaTime,CircuitTrack* circuit)
{
    ArgumentConflictInfo conflictInfo;
    //�Ԃ̍X�V�@�R�[�X�O�ɏo�����ǂ����������Œ��ׂ�
    lacer.car->Update(deltaTime, circuit->GetOutsideHitFlag(lacer.car));
    //�`�F�b�N�|�C���g�̍X�V�̍X�V
    conflictInfo.SetObjInfo(true, lacer.car);
    lacer.checkPoint->Update(conflictInfo);
    //�ԂɎ��̃`�F�b�N�|�C���g�����������ׂ�
    if (hitChecker.HitCheck(lacer.car, lacer.checkPoint))
    {
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

void LacerManager::LacerLoop(void(LacerManager::* function)(Lacer))
{
    std::list<Lacer>::iterator lacerIte;
    ArgumentConflictInfo conflictInfo;
    for (lacerIte = lacerList.begin(); lacerIte != lacerList.end(); lacerIte++)
    {
       (this->(*function))(*lacerIte);
    }
}

void LacerManager::LacerLoop(void(*function)(Lacer, float, CircuitTrack*), float deltaTime, CircuitTrack* circuit)
{
}


/// <summary>
  /// �`��
  /// </summary>
  /// <returns></returns>
void LacerManager::Draw()
{
    std::list<Lacer>::iterator lacerIte;
    Lacer lacer;
    for (lacerIte = lacerList.begin(); lacerIte != lacerList.end(); lacerIte++)
    {
        lacer = *lacerIte;
        lacer.car->Draw();
    }
}
/// <summary>
/// ��ԍŏ��ɒǉ������I�u�W�F�N�g��Ԃ�
/// </summary>
/// <returns></returns>
Object* LacerManager::GetPlayer() const
{
    return lacerList.front().car;
}

