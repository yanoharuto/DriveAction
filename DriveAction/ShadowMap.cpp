#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
    //かげの向き
    SetShadowMapLightDirection(shadowMap, VGet(0.2f, -1, 0));
    SetShadowMapDrawArea(shadowMap, DrawAreaMinPos, DrawAreaMaxPos);
}

ShadowMap::~ShadowMap()
{
    DeleteShadowMap(shadowMap);
}

void ShadowMap::SetShadowMapErea(ObjInfo objInfo)
{
    VECTOR minPos = VAdd(objInfo.pos, DrawAreaMinPos);
    VECTOR maxPos = VAdd(objInfo.pos, DrawAreaMaxPos);
    SetShadowMapDrawArea(shadowMap, minPos, maxPos);
}
//描画に使用するシャドウマップを設定
void ShadowMap::SetUP()
{
    ShadowMap_DrawSetup(shadowMap);
}

void ShadowMap::DrawEnd()
{
    //シャドウマップへの描画を終了
    ShadowMap_DrawEnd();
    SetUseShadowMap(0, shadowMap);
}

void ShadowMap::Use()
{
    SetUseShadowMap(0, -1);
}
