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
    //シャドウマップの範囲を設定
    VECTOR DrawAreaMinPos = VGet(-700.0f, -1.0f, -700.0f);
    VECTOR DrawAreaMaxPos = VGet(700.0f, 1000.0f, 700.0f);
    //シャドウマップ作製
    int shadowMap = MakeShadowMap(1024, 1024);
};

