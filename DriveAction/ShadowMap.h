#pragma once
#include "DxLib.h"
#include "ObjPosAndDir.h"
class ShadowMap
{
public:
    ShadowMap();
    ~ShadowMap();
    void SetShadowMapErea(ObjInfo objInfo);
    void SetUP();
    void DrawEnd();
    void Use();
private:
    //�V���h�E�}�b�v�͈̔͂�ݒ�
    VECTOR DrawAreaMinPos = VGet(-700.0f, -1.0f, -700.0f);
    VECTOR DrawAreaMaxPos = VGet(700.0f, 1000.0f, 700.0f);
    //�V���h�E�}�b�v�쐻
    int shadowMap = MakeShadowMap(1024, 1024);
};

