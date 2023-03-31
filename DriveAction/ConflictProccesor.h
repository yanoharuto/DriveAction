#pragma once
#include <list>
#include <unordered_map>
#include "Timer.h"
#include "ConflictExamineResultInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "Actor.h"
/// <summary>
/// �����蔻����s��
/// </summary>
class  ConflictProccesor abstract
{
public:
    ConflictProccesor() {};
    ConflictProccesor(Actor* obj);
    virtual ~ConflictProccesor();
    /// <summary>
    /// �����蔻����s��
    /// </summary>
    /// <param name="hitCheckInfo"></param>
    /// <returns></returns>
    virtual ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo hitCheckInfo) = 0;
    /// <summary>
    /// �����蔻��ŕK�v�ȏ���n��
    /// </summary>
    /// <returns></returns>
    virtual HitCheckExamineObjectInfo GetHitExamineCheckInfo();
    /// <summary>
    /// �����蔻��̏������Ăяo��
    /// </summary>
    /// <param name="resultInfo"></param>
    virtual void ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo);
    /// <summary>
    /// �����蔻��œ���̂��̂ɃN�[���^�C������������ꍇ�^�C�}�[���Z�b�g�o����
    /// </summary>
    /// <param name="tag">����̎҂̃^�O</param>
    /// <param name="timer">�N�[���^�C���v���p�̃^�C�}�[</param>
    void SetCoolTimer(ObjectTag tag,Timer* timer);
protected:
    //�����蔻��̎�����
    Actor* object = nullptr;
    //�N�[���^�C�}�[
    std::unordered_map<ObjectTag, Timer*> coolTimer;
};