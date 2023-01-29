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
    tag = ObjectTag::obstacle;
    MV1SetPosition(modelHandle,position);
    radius = setRadius;
}

Saw::~Saw()
{
}

void Saw::Update()
{
}

void Saw::Draw()
{
    MV1DrawModel(modelHandle);
}
