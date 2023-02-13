#pragma once
#include "Racer.h"
#include "PlayerCar.h"
#include "PlayerRelatedInfo.h"
#include "PlaySceneCamaeraArgumentInfo.h"
class Player final:
    public Racer 
{
public:
    Player();
    Player(CircuitData circuitData, VECTOR firstPos, VECTOR firstDir);
    ~Player();
    void Update(float deltaTime, bool outsideHitFlag, DamageObjectGenerator* damageObjGene)override;
    PlayerRelatedInfo GetRelatedInfo();
    PlaySceneCameraArgumentInfo GetCameraArgumentInfo();
private:
    PlayerCar* playerCar = nullptr;
};

