#include "LacerManager.h"
#include "CPUCar.h"
#include "Goal.h"
#include "Player.h"
#include "Utility.h"
#include "CircuitTrack.h"

/// <summary>
/// ������
/// </summary>
/// <param name="lacerNum">�ԏ��̐��������X�g�ɒǉ������</param>
/// <returns></returns>
LacerManager::LacerManager(int lacerNum)
{
    Lacer lacer{};
    lacer.rank = lacerNum;
    lacer.goal = new Goal(1, "goalStatus.txt");
    lacer.car = new Player();
    lacerList.push_back(lacer);
    for (int i = lacerNum; i > 0; i--)
    {
        lacer.car = new CPUCar();
        lacer.goal = new Goal(lacerList.front().goal->GetCheckPoint());
        lacer.rank = i - 1;
        lacerList.push_back(lacer);
        ArgumentConflictInfo conflictInfo = MakeArgumentInfo(lacer.goal);
        lacer.car->ConflictProcess(conflictInfo);
    }
}
//�f�X�g���N�^
LacerManager::~LacerManager()
{
    for (int i = 0; i < static_cast<signed>(lacerList.max_size()); i++)
    {
        SAFE_DELETE(lacerList.front().car);
        SAFE_DELETE(lacerList.front().goal);
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
        lacer.car->Update(deltaTime, circuit->GetOutsideHitFlag(lacer.car));
        conflictInfo = MakeArgumentInfo(lacer.car);
        if (hitChecker.HitCheck(lacer.goal,lacer.car))
        {
            lacer.goal->Update(lacer.car);
            conflictInfo = MakeArgumentInfo(lacer.goal);
            lacer.car->ConflictProcess(conflictInfo);
        }
        conflictInfo = circuit->GetGurdHitFlag(lacer.car);
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
