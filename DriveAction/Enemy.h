#pragma once
#include "CPUCar.h"
class Enemy :
    public CPUCar
{
public:

    Enemy(CarParamater carParam, int duplicateModelHandle);;
    ~Enemy();
    virtual void Update(const float deltaTime, VECTOR playerPos, ItemInfo itemInfo);
    virtual void Draw();
private:
    const float scale = 8.0f;
    
};

