#include "SkyDome.h"
/// <summary>
/// modelのロードとタグ付け
/// </summary>
/// <returns></returns>
SkyDome::SkyDome()
{
    modelHandle = MV1LoadModel("data/model/SkyDome/SkyDome.mv1");
    MV1SetPosition(modelHandle, position);
    MV1SetScale(modelHandle, VGet(setSize, setSize, setSize));
    tag = ObjectTag::stage;
}
//modelのデリート
SkyDome::~SkyDome()
{
    MV1DeleteModel(modelHandle);
}
/// <summary>
/// modelの描画
/// </summary>
void SkyDome::Draw()
{
    SetUseLighting(false);
    MV1DrawModel(modelHandle);
    SetUseLighting(true);
}
