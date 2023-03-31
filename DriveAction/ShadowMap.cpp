#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
    //�����̌���
    SetShadowMapLightDirection(shadowMap, VGet(1.0f, -1, 0));
    SetShadowMapDrawArea(shadowMap, DrawAreaMinPos, DrawAreaMaxPos);
}

ShadowMap::~ShadowMap()
{
    DeleteShadowMap(shadowMap);
}
/// <summary>
/// �e�̕`��͈͂̕ύX
/// </summary>
/// <param name="objInfo">�����̍��W�𒆐S�ɂ���</param>
void ShadowMap::SetShadowMapErea(ObjInfo objInfo)
{
    VECTOR minPos = VAdd(objInfo.pos, DrawAreaMinPos);
    VECTOR maxPos = VAdd(objInfo.pos, DrawAreaMaxPos);
    SetShadowMapDrawArea(shadowMap, minPos, maxPos);
}
/// <summary>
/// ���ꂩ��`�悷��e�̏���
/// </summary>
void ShadowMap::SetUP()
{
    ShadowMap_DrawSetup(shadowMap);
}
/// <summary>
/// �e��`�悷��̏I��
/// </summary>
void ShadowMap::DrawEnd()
{
    //�V���h�E�}�b�v�ւ̕`����I��
    ShadowMap_DrawEnd();
    SetUseShadowMap(0, shadowMap);
}
/// <summary>
/// �������񂾃V���h�E�}�b�v���g��
/// </summary>
void ShadowMap::Use()
{
    SetUseShadowMap(0, -1);
}
