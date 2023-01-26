#pragma once
#include "Object.h"
#include "DxLib.h"
class AccelerationFloor :
    public Object
{
public:
    AccelerationFloor();
    AccelerationFloor(VECTOR pos, VECTOR dir);
    ~AccelerationFloor();
    void Update();
    void Draw();
private:
    const float addAccel = 50.0f;
    const float setRadius = 35.0f;
    const float setScale = 5.0f;
    int effekseerModelHandle;
    int playingEffect;

};