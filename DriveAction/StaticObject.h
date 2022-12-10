#pragma once
#include "DxLib.h"
class StaticObject
{
public:
    StaticObject() {}
    virtual ~StaticObject() {}
    virtual void Draw() {}
protected:
    int ModelHandele;
    VECTOR Position;
    VECTOR Velocity;
    VECTOR Direction;
};