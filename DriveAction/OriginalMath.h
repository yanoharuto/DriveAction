#pragma once
#include "DxLib.h"
#include <math.h>
#include<random>
#define RAGE  static_cast<float>(DX_PI / 180.0f) //ラジアン

class OriginalMath
{
public:
    /// <summary>
    /// 第一引数と第二引数の角度のずれを出す
    /// </summary>
    /// <param name="direction1"></param>
    /// <param name="direction2"></param>
    /// <returns>デグリーで返す</returns>
    static float GetDegreeMisalignment(VECTOR direction1, VECTOR direction2)
    {
        float destinationDir = 0;
        destinationDir = VDot(direction1, direction2) / (VSize(direction2) * VSize(direction1));
        destinationDir = acosf(destinationDir) / RAGE;
        return destinationDir;
    }
    static int GetRandom(int min, int max)
    {
        std::random_device seed;
        std::mt19937 engine(seed());
        std::uniform_int_distribution<> dist{ min,max };
        return dist(engine);
    }
    static VECTOR GetYRotateVector(VECTOR rotateVector, float degree)
    {
        float rage = degree * RAGE;
        VECTOR addVec = degree > 0 ? VGet(0, 1, 0) : VGet(0, -1, 0);
        addVec = VScale(VNorm(VCross(rotateVector, addVec)), rage);
        rotateVector = VAdd(rotateVector, addVec);
        return rotateVector;
    }
};