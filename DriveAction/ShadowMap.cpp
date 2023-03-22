#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
    //�����̌���
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
//�`��Ɏg�p����V���h�E�}�b�v��ݒ�
void ShadowMap::SetUP()
{
    ShadowMap_DrawSetup(shadowMap);
}

void ShadowMap::DrawEnd()
{
    //�V���h�E�}�b�v�ւ̕`����I��
    ShadowMap_DrawEnd();
    SetUseShadowMap(0, shadowMap);
}

void ShadowMap::Use()
{
    SetUseShadowMap(0, -1);
}
