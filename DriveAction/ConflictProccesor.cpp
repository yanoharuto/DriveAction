#include "conflictProccesor.h"
#include "HitChecker.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
ConflictProccesor::ConflictProccesor(Actor* obj)
{
    object = obj;
    ConflictManager::AddConflictObjInfo(this);
}

ConflictProccesor::~ConflictProccesor()
{

}
/// <summary>
/// �����蔻��ŕK�v�ȏ���n��
/// </summary>
/// <returns></returns>
HitCheckExamineObjectInfo ConflictProccesor::GetHitExamineCheckInfo()
{
    HitCheckExamineObjectInfo info;
    info.SetExamineInfo(object);
    info.velocity = object->GetVelocity();
    return info;
}
/// <summary>
/// �����蔻��̏������Ăяo��
/// </summary>
/// <param name="resultInfo"></param>
void ConflictProccesor::ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo)
{
    for (auto ite = resultInfo.begin(); ite != resultInfo.end(); ite++)
    {
        if ((*ite).hit != HitSituation::NotHit)
        {
            if (coolTimer.contains((*ite).tag))
            {
                //�N�[���^�C�����߂��Ă��ē������Ă���Ȃ�
                if (coolTimer[(*ite).tag]->IsOverLimitTime())
                {
                    //�����������̏������s��
                    object->ConflictProccess((*ite));
                }
            }
            else
            {
                //�����������̏������s��
                object->ConflictProccess((*ite));
            }
        }
    }
}
/// <summary>
/// �����蔻��œ���̂��̂ɃN�[���^�C������������ꍇ�^�C�}�[���Z�b�g�o����
/// </summary>
/// <param name="tag">����̎҂̃^�O</param>
/// <param name="timer">�N�[���^�C���v���p�̃^�C�}�[</param>
void ConflictProccesor::SetCoolTimer(ObjectTag tag,Timer* timer)
{
    coolTimer.insert(std::make_pair(tag, timer));
}
