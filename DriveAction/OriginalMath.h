#pragma once
#include "DxLib.h"
#include <math.h>
#define RAGE  static_cast<float>(DX_PI / 180.0f) //���W�A��

class OriginalMath
{
public:
    OriginalMath() {};
    ~OriginalMath() {};
    /// <summary>
    /// �������Ƒ������̊p�x�̂�����o��
    /// </summary>
    /// <param name="direction1"></param>
    /// <param name="direction2"></param>
    /// <returns></returns>
    float GetDegreeMisalignment(VECTOR direction1, VECTOR direction2)
    {
        float destinationDir = 0;
        destinationDir = VDot(direction1, direction2) / (VSize(direction2) * VSize(direction1));
        destinationDir = acosf(destinationDir) / RAGE;
        return destinationDir;
    }
};