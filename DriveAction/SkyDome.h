#pragma once
#include "DxLib.h"

/// <summary>
/// スカイドーム
/// </summary>
class SkyDome final
{
public:
    SkyDome();
    ~SkyDome();
    void Update();
    void Draw();
private:
    //描画モデル
    int modelHandle;
    //場所
    VECTOR position;
    VECTOR scale;
    float const scaleValue = 15.0f;
};

