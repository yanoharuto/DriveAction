#include "Player.h"
#include"Utility.h"
Player::Player()
{
}

Player::Player(CircuitData circuitData, VECTOR firstPos, VECTOR firstDir)
    :Racer(circuitData)
{
    playerCar = new PlayerCar(firstPos,firstDir,checkPoint->GetPos());
    SetCarPointer(playerCar);
}

Player::~Player()
{
}

void Player::Update(float deltaTime, bool outsideHitFlag, DamageObjectGenerator* damageObjGene)
{
    ItemInfo itemInfo = itemHolder->GetItemInfo();
    CommonUpdate(deltaTime,outsideHitFlag,damageObjGene);
    int inputKey = GetJoypadInputState(DX_INPUT_KEY);
    if ((inputKey & PAD_INPUT_10 || itemInfo.itemSituation == ItemUseSituation::Useing) && itemInfo.itemTag != non)
    {
        itemHolder->UseItem(car->GetItemArgumentInfo());
    }
}

PlayerRelatedInfo Player::GetRelatedInfo()
{
    PlayerRelatedInfo info = {};
    info.accelPower = car->GetTotalAccelPowerPercent();
    info.carDirection = car->GetDir();
    info.itemTag = itemHolder->GetItemInfo().itemTag;
    info.lap = checkPoint->GetGoalCount();
    info.rank = rank;
    info.nextCheckPointDirection = checkPoint->GetDir();
    return info;
}

PlaySceneCameraArgumentInfo Player::GetCameraArgumentInfo()
{
    PlaySceneCameraArgumentInfo argumentInfo = {};
    argumentInfo.dir = playerCar->GetDir();
    argumentInfo.pos = playerCar->GetPos();
    argumentInfo.handleDir = playerCar->GetHandleDirection();
    return argumentInfo;
}
