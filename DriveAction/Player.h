#pragma once
#include "Actor.h"
class Player final: public Actor
{
public:
    Player();
    ~Player();
    void Update() override;
    void Draw() override;
    VECTOR GetPos();
};

