#pragma once
#include "DxLib.h"

/// <summary>
/// �X�J�C�h�[��
/// </summary>
class SkyDome final
{
public:
    SkyDome();
    ~SkyDome();
    void Update();
    void Draw();
private:
    //�`�惂�f��
    int modelHandle;
    //�ꏊ
    VECTOR position;
    VECTOR scale;
    float const scaleValue = 15.0f;
};

