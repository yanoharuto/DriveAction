#include "Saw.h"

Saw::Saw()
{
}

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

void Saw::Update(const float deltaTime)
{
}

