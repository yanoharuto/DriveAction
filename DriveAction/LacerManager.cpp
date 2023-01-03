#include "LacerManager.h"
#include "CPUCar.h"
#include "CheckPoint.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"

/// <summary>
/// ������
/// </summary>
/// <param name="lacerNum">�ԏ��̐��������X�g�ɒǉ������</param>
/// <returns></returns>
LacerManager::LacerManager(int cpuNum)
{
    Lacer lacer{};
    lacer.rank = cpuNum + 1;
    lacer.checkPoint = new CheckPoint(1, "goalStatus.txt");
    lacer.car = new Player();
    lacerList.push_back(lacer);
    for (int i = cpuNum; i > 0; i--)
    {
        lacer.car = new CPUCar();
        lacer.checkPoint = new CheckPoint(lacerList.front().checkPoint->GetCheckPoint());
        lacer.rank = i;
        lacerList.push_back(lacer);
        ArgumentConflictInfo conflictInfo = MakeArgumentInfo(lacer.checkPoint);
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
    std::list<Lacer>::iterator lacerIte;
    Lacer lacer;
    ArgumentConflictInfo conflictInfo;
    for(lacerIte = lacerList.begin();lacerIte!=lacerList.end();lacerIte++)
    {
        lacer = *lacerIte;
        //�Ԃ̍X�V�@�R�[�X�O�ɏo�����ǂ����������Œ��ׂ�
        lacer.car->Update(deltaTime, circuit->GetOutsideHitFlag(lacer.car));
        if (hitChecker.HitCheck(lacer.checkPoint,lacer.car))
        {
            lacer.checkPoint->Update(lacer.car);

            conflictInfo = MakeArgumentInfo(lacer.checkPoint);
            lacer.car->ConflictProcess(conflictInfo);
        }
        conflictInfo = circuit->GetCourceConflictInfo(lacer.car);
        if (conflictInfo.hitFlag)
        {
            lacer.car->ConflictProcess(conflictInfo);
        }
    }
}
/// <summary>
/// �����̕��̂ɂԂ����������ׂ�
/// </summary>
/// <param name="obj">���ׂ�������</param>
void LacerManager::ArgumentConflictProcess(Object* obj)
{
    ArgumentConflictInfo conflictInfo = MakeArgumentInfo(obj);
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
/// <summary>
  /// �����̃I�u�W�F�N�g�̓����蔻���񏊓�
  /// </summary>
  /// <param name="obj">�����蔻��𒲂ׂ����I�u�W�F�N�g</param>
  /// <returns>�����Ƃ��ēn���������</returns>

ArgumentConflictInfo LacerManager::MakeArgumentInfo(Object* obj)
{
    return { true ,obj->GetTag(),obj->GetPos(),obj->GetRadius() };
}
