#include "Saw.h"

Saw::Saw()
{
}
/// <summary>
/// ˆø”‚ÌêŠ‚Éİ’u‚·‚é
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
/// ‰ñ“]‚³‚¹‚é
/// </summary>
/// <param name="deltaTime"></param>
void Saw::Update(const float deltaTime)
{
    rotate = addRotate * deltaTime;
    MATRIX matY = MGetRotY(rotate);
    MV1SetRotationMatrix(modelHandle, matY);
}
/// <summary>
/// ˆø”‚Ì•¨‘Ì‚É“–‚½‚Á‚Ä‚é‚©•Ô‚·
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

