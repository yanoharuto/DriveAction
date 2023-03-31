#include "ConflictProccesor.h"
/// <summary>
/// �X�e�[�W�̏�Q���Ƃ��̓����蔻��
/// </summary>
class MeshCollider final :public ConflictProccesor
{
public:
    /// <summary>
    /// ���f���n���h�����瓖���蔻������ 
    /// </summary>
    MeshCollider(int setModelHandle, ObjectTag setTag);
    ~MeshCollider()override;
    /// <summary>
    /// �����蔻���Ԃ�
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo)override;
    /// <summary>
    /// ���Ƃ̓����蔻��
    /// </summary>
    /// <param name="examineInfo"></param>
    /// <returns></returns>
    ConflictExamineResultInfo GetSphereConflictModelInfo(HitCheckExamineObjectInfo examineInfo);
    /// <summary>
    /// mesh�Ȃ̂ňʒu�Ƃ��͋�����Ȃ�
    /// </summary>
    /// <returns></returns>
    HitCheckExamineObjectInfo GetHitExamineCheckInfo()override;
    /// <summary>
    /// ���������ꍇ�̔���
    /// </summary>
    /// <param name="resultInfo"></param>
    void ConflictProccess(std::list<ConflictExamineResultInfo> resultInfo)override;
private:
    int modelHandle = -1;
    ObjectTag tag = ObjectTag::stage;
    float bouncePower;
};