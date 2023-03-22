#include "Player.h"
#include "Utility.h"
#include "Rule.h"
#include "UserInput.h"
Player::Player()
{
}

Player::Player(VECTOR firstPos)
    :Racer()
{
    car = new PlayerCar(firstPos);
    SetCarPointer(car);
    SoundPlayer::LoadSound(rouletteSE);
}

Player::~Player()
{
    
}

void Player::Update(float deltaTime)
{
    ItemInfo itemInfo = itemHolder->GetItemInfo();
    
    car->Update(deltaTime, {0,0,0}, itemInfo);
    if (checkPoint->IsTransitCheckPoint(transitCPCount, car->GetHitCheckExamineInfo()))
    {
        transitCPCount++;
    }
    if ((UserInput::GetInputState(Space) == Push || itemInfo.itemSituation == ItemUseSituation::Useing) && itemInfo.itemTag != non)
    {
        ItemArgumentCarInfo itemArgumentInfo;
        itemArgumentInfo.SetCarInfo(car);
        itemHolder->UseItem(itemArgumentInfo);
    }
}

PlayerRelatedInfo Player::GetRelatedInfo()
{
    PlayerRelatedInfo info = {};
    info.accelPower = car->GetTotalAccelPower();
    info.accelPowerParcent = car->GetTotalAccelPowerPercent();
    info.reverseDrive = reverse;
    info.itemTag = itemHolder->GetItemInfo().itemTag;
    info.lap = checkPoint->GetGoalCount(transitCPCount);
    info.transitCount = transitCPCount;
    info.rank = rank;
    info.HP = hp;
    info.objInfo = car->GetCarPosAndDir();
    info.isAlive = car->GetAliveFlag();
    return info;
}

ObjInfo Player::GetPlayerPosAndDir()
{
    return car->GetCarPosAndDir();
}