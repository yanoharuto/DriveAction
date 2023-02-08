#include "Player.h"

Player::Player()
{
}

Player::Player(CircuitData circuitData, VECTOR firstPos, VECTOR firstDir)
    :Racer(circuitData)
{
    playerCar = new PlayerCar(firstPos,firstDir,checkPoint->GetPos(), soundPlayer);
    SetCarPointer(playerCar);
}

Player::~Player()
{
}

void Player::Update(float deltaTime, bool outsideHitFlag, FiringItemManager* firingItemManager)
{


    ItemInfo itemInfo = itemHolder->GetItemInfo();
    car->Update(deltaTime, outsideHitFlag, itemInfo, soundPlayer);
    int inputKey = GetJoypadInputState(DX_INPUT_KEY);
    if ((inputKey & PAD_INPUT_10 || itemInfo.itemSituation == ItemUseSituation::Useing) && itemInfo.itemTag != non)
    {
        itemHolder->ShowItem();
    }
    itemHolder->Update(firingItemManager, car->GetItemArgumentInfo(), deltaTime);
    HitCheckExamineObjectInfo racerHitCheckExamineInfo;
    racerHitCheckExamineInfo.SetExamineInfo(*car);
    //車がチェックポイントを通過したか調べる
    ConflictExamineResultInfo conflictResultInfo;
    conflictResultInfo = checkPoint->CheckPointUpdate(racerHitCheckExamineInfo);
    if (conflictResultInfo.hitFlag)
    {
        //車に次の目的地を伝える
        car->ConflictProcess(deltaTime, conflictResultInfo, soundPlayer);
    }
}

PlayerRelatedInfo Player::GetRelatedInfo()
{
    PlayerRelatedInfo info;
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
    PlaySceneCameraArgumentInfo argumentInfo;
    argumentInfo.dir = playerCar->GetDir();
    argumentInfo.pos = playerCar->GetPos();
    return argumentInfo;
}
