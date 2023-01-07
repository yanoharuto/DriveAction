#pragma once
#include <List>
#include <string>
#include "HitChecker.h"
class Object;
class CheckPoint;
class Car;
class CircuitTrack;
/// <summary>
/// �����蔻��Ŏg���n���Ăق������
/// Actor�ɒ�`
/// </summary>
struct  ArgumentConflictInfo;
/// <summary>
/// �����Ă�Ԃ̏��
/// </summary>
struct Lacer
{
    int rank;
    CheckPoint* checkPoint;
    Car* car;
};
/// <summary>
/// �ԏ��̃}�l�[�W���[
/// </summary>
class LacerManager
{
public:

    LacerManager() {};
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="lacerNum">�ԏ��̐��������X�g�ɒǉ������</param>
    /// <returns></returns>
    LacerManager(int cpuNum,std::string chcekPointAddress);
    //�f�X�g���N�^
    ~LacerManager();
    /// <summary>
    /// �ԏ�肽���̍X�V
    /// </summary>
    /// <param name="deltaTime">�t���[���Ԃ̌o�ߎ���</param>
    /// <param name="circuit">����R�[�X</param>
    void Update(const float deltaTime, CircuitTrack* circuit);
    /// <summary>
    /// �����̕��̂ɂԂ����������ׂ�
    /// </summary>
    /// <param name="obj"></param>
    void ArgumentConflictProcess(Object* obj);

    /// <summary>
    /// �`��
    /// </summary>
    /// <returns></returns>
    void Draw();
    /// <summary>
    /// ��ԍŏ��ɒǉ������I�u�W�F�N�g��Ԃ�
    /// </summary>
    /// <returns></returns>
    Object* GetPlayer() const;
    /// <summary>
    /// �ԏ�肽�����m�łԂ����ĂȂ������ׂ�
    /// </summary>
    void LacerConflictProcces();

private:
    void LacerUpdateProcces(Lacer ,float ,CircuitTrack* );
    void LacerLoop(void(LacerManager::*function)(Lacer));
    void LacerLoop(void(LacerManager::*function)(Lacer,float,CircuitTrack*), float deltaTime, CircuitTrack* circuit);

    //�ԏ��B�̃��X�g
    std::list<Lacer> lacerList;
    //�������Ă邩�ǂ������ׂ�
    HitChecker hitChecker;
};

