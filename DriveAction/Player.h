#pragma once
#include "DxLib.h"
class Player final
{
public:
    Player();
    ~Player();
    void Update();
    void Draw();
    VECTOR GetPos();

private:
    int  modelHandle;
    VECTOR Position;
    VECTOR Velocity;
    VECTOR Direction;

};

