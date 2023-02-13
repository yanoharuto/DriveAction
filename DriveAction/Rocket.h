#pragma once
#include "DamageObject.h"
#include "ItemArgumentCarInfo.h"
#include "DxLib.h"
class Rocket final :public DamageObject
{
public:
    Rocket() {};
    Rocket(ItemArgumentCarInfo carInfo);
    ~Rocket();
    void Update(float deltaTime)override;
    void ConflictProccess()override;
private:
    std::string rocketModelAddress = "data/model/Item/Rocket/Rocket04_Grey.mv1";
    float fallingSpeed = 24.5f;
    float setBouncePower = 4.25f;
    const float gravityPower = 0.9f;
    const float setSize = 1.000f;
    const float setRadius = 2.0f;
    int effectResource = -1;
    int playEffect = -1;
    bool onGround = -1;
};

