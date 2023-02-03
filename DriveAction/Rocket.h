#pragma once
#include "Actor.h"
#include "DxLib.h"
class Rocket final :public Actor
{
public:
    Rocket();
    Rocket(VECTOR pos,int modelResourceHandle);
    ~Rocket();
    void Update();
    void Draw();
private:
    std::string rocketModelAddress = "data/model/Roket/Rocket04_Grey.mv1";
    const float gravityPower = 0.9f;
    float fallingSpeed = 1;
    float setBouncePower = 15;
};

