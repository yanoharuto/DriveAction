#pragma once
#include "DamageObject.h"
#include "ItemArgumentCarInfo.h"
#include "DxLib.h"
class Rocket final :public DamageObject
{
public:
    Rocket() {};
    Rocket(ItemArgumentCarInfo carInfo,int modelResourceHandle);
    ~Rocket();
    void Update(float deltaTime)override;
    void ConflictProccess()override;
private:

    float fallingSpeed = 24.5f;
    float setBouncePower = 4.25f;
    const float gravityPower = 0.9f;
    const float setSize = 1.000f;
    const float setRadius = 2.0f;
    int effectResource;
    int playEffect;
    bool onGround;
};

