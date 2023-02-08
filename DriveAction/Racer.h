#pragma once
#include "CircuitDataStruct.h"
#include "SoundPlayer.h"
#include "ItemHolder.h"
#include "Car.h"
#include "CheckPoint.h"
#include "ConflictExamineResultInfo.h"
class Racer abstract
{
public:
    Racer();
    Racer(CircuitData circuitData);
    virtual ~Racer();
    virtual void Update(float deltaTime,bool outsideHitFlag,FiringItemManager* firingItemManager);
    bool HitCheck(HitCheckExamineObjectInfo objInfo);
    void Draw();
    void ConflictProcces(ConflictExamineResultInfo conflictResultInfo,float deltaTime);

    HitCheckExamineObjectInfo GetCarHitCheckExamineInfo();
    ConflictExamineResultInfo GetConflictExamineResultInfo();
    int* GetRankPointer();
    CheckPoint* GetCheckPointer();
protected:
    void SetCarPointer(Car* car);
    int rank;
    CheckPoint* checkPoint;
    Car* car;
    SoundPlayer* soundPlayer;
    ItemHolder* itemHolder;
};

