#include "SkyDome.h"
/// <summary>
/// model�̃��[�h�ƃ^�O�t��
/// </summary>
/// <returns></returns>
SkyDome::SkyDome()
{
    modelHandle = MV1LoadModel("data/model/SkyDome/SkyDome.mv1");
    MV1SetPosition(modelHandle, position);
    MV1SetScale(modelHandle, VGet(setSize, setSize, setSize));
    tag = ObjectTag::stage;
}
//model�̃f���[�g
SkyDome::~SkyDome()
{
    MV1DeleteModel(modelHandle);
}
/// <summary>
/// model�̕`��
/// </summary>
void SkyDome::Draw()
{
    SetUseLighting(false);
    MV1DrawModel(modelHandle);
    SetUseLighting(true);
}
