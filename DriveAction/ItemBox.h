#pragma once
#include "Actor.h"
class ItemBox :
    public Actor
{
public:
    ItemBox();
    ItemBox(int modelResourceHandle,VECTOR pos, VECTOR dir);
    ~ItemBox();
    void Update(const float deltaTime)override;

    void ConflictProccess(const ConflictExamineResultInfo conflictInfo)override;
private:
    float scale = 0;
    float recoveryTime = 0;
    const float setRadius = 15.0f;
    const float setRecoveryTime = 1.0f;
    const float addScale = 80.0f;
    const float setMaxScale = 80;
};

