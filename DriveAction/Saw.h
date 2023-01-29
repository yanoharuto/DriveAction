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
    const float setRadius = 26.0f;
    const float setBouncePower = 4.0f;
    int modelHandle;
};
