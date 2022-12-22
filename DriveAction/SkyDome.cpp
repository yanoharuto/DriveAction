#include "SkyDome.h"

SkyDome::SkyDome()
    :position({}),
    modelHandle(-1)
{
    modelHandle = MV1LoadModel("data/model/SkyDome/SkyDome.mv1");
    scale = VGet(scaleValue, scaleValue, scaleValue);
    MV1SetScale(modelHandle, scale);
    MV1SetPosition(modelHandle, position);
}

SkyDome::~SkyDome()
{
    MV1DeleteModel(modelHandle);
}

void SkyDome::Update()
{
}

void SkyDome::Draw()
{
    MV1DrawModel(modelHandle);
}
