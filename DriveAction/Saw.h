#pragma once
#include "Object.h"
#include "DxLib.h"
/// <summary>
/// ��Q���@�i�ۂ̂��j
/// </summary>
class Saw :
    public Object
{
public:
    Saw();
    Saw(VECTOR pos, int duplicateModelHandle);
    ~Saw();
    void Update();
    void Draw();
private:
    const float addRotate = 0.02f;
    int modelHandle;
};

