#pragma once
#include <list>
#include <string>
#include "DamageObject.h"
#include "CircuitTrack.h"
#include "ItemArgumentCarInfo.h"
#include "ItemTag.h"
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
    void AddDamageObject(DamageObject* damageObj);
    /// <summary>
    /// �Փ�
    /// </summary>
    /// <param name="conflictProccess"></param>
    void CircuitTrackConflictProccess(CircuitTrack* conflictProccess);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="deltaTime"></param>
    void Update(float deltaTime);
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();
private:
    //�I�u�W�F�N�g�^�O��DamageObject�ɂȂ��Ă�I�u�W�F�N�g�̃��X�g
    std::list<DamageObject*> damageObjList;
};