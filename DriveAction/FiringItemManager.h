#pragma once
#include <list>
#include "CircuitTrack.h"
#include "DamageObjectGenerator.h"
/// <summary>
/// ��ѓ���̖ʓ|������z
/// </summary>
class FiringItemManager
{
public:

    /// <summary>
    /// ���������Ƃ��ɒǉ�����
    /// </summary>
    /// <param name="conflictProcesser"></param>
    FiringItemManager();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~FiringItemManager();
    /// <summary>
    /// �����A�C�e����ǉ�
    /// </summary>
    /// <param name="itemTag"></param>
    /// <param name="carInfo"></param>
    static void AddFiringObject(Actor* damageObj);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update();
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();
private:
    DamageObjectGenerator* damageObjGenerator;

    //�I�u�W�F�N�g�^�O��DamageObject�ɂȂ��Ă�I�u�W�F�N�g�̃��X�g
    static std::list<Actor*> damageObjList;
};