#include "ItemBox.h"

ItemBox::ItemBox()
{
}

ItemBox::ItemBox(int modelResourceHandle, VECTOR pos, VECTOR dir)
{
    position = pos;
    direction = dir;
    modelHandle = MV1DuplicateModel(modelResourceHandle);
    tag = ObjectTag::itemBox;
    scale = setMaxScale;
    radius = setRadius;
    recoveryTime = -1;
    MV1SetScale(modelHandle, VGet(scale,scale,scale));
    MV1SetPosition(modelHandle,pos);
}

ItemBox::~ItemBox()
{
}

void ItemBox::Update(const float deltaTime)
{
    if (recoveryTime > 0)
    {
        recoveryTime -= deltaTime;
    }
    else
    {
        if (scale < setMaxScale)
        {
            scale = scale + addScale * deltaTime;
        }
        else
        {
            scale = setMaxScale;
        }
    }
    MV1SetScale(modelHandle, VGet(scale, scale, scale));
}

bool ItemBox::HitCheckConflict(const HitCheckExamineObjectInfo examineObjInfo)
{
    if (recoveryTime < 0)
    {
        HitChecker checker;
        return  checker.HitCheck(this, examineObjInfo);
    }
    else
    {
        return false;
    }
}

void ItemBox::ConflictProccess()
{
    recoveryTime = setRecoveryTime;
    scale = 0;
}