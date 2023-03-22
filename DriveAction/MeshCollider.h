#include "ConflictProccesor.h"

class MeshCollider final :public ConflictProccesor
{
public:
    MeshCollider() {};
    MeshCollider(int setModelHandle,ConflictExamineResultInfo setResultInfo);
    ~MeshCollider()override;
    ConflictExamineResultInfo HitCheck(HitCheckExamineObjectInfo)override;
    ConflictExamineResultInfo GetSphereConflictModelInfo(HitCheckExamineObjectInfo examineInfo);
    HitCheckExamineObjectInfo GetHitExamineCheckInfo()override;
    void ConflictProccess(ConflictExamineResultInfo resultInfo)override;
private:
    int modelHandle = -1;
    ObjectTag tag=ObjectTag::stage;
    float bouncePower;
};