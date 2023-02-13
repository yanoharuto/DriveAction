#include "Saw.h"

Saw::Saw()
{
}
/// <summary>
/// �����̏ꏊ�ɐݒu����
/// </summary>
/// <param name="pos"></param>
/// <param name="duplicateModelHandle"></param>
Saw::Saw(VECTOR pos, int duplicateModelHandle)
{
    position = pos;
    bouncePower = setBouncePower;
    direction = {};
    int duplicateModel = MV1DuplicateModel(duplicateModelHandle);
    modelHandle = duplicateModel;
    tag = ObjectTag::damageObject;
    MV1SetPosition(modelHandle,position);
    radius = setRadius;
}

Saw::~Saw()
{
}

/// <summary>
/// ��]������
/// </summary>
/// <param name="deltaTime"></param>
void Saw::Update(const float deltaTime)
{
    rotate = addRotate * deltaTime;
    MATRIX matY = MGetRotY(rotate);
    MV1SetRotationMatrix(modelHandle, matY);
}
/// <summary>
/// �����̕��̂ɓ������Ă邩�Ԃ�
/// </summary>
/// <param name="examineObjInfo"></param>
/// <returns></returns>
bool Saw::HitCheckConflict(const HitCheckExamineObjectInfo examineObjInfo)
{
    float absfY = fabsf(position.y - examineObjInfo.pos.y);
    if (absfY < thickness)
    {
        return HitChecker::HitCheck(this, examineObjInfo);
    }
    return false;
}

