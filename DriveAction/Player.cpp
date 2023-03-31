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
    hitNumCounter = new HitNumCounter(3.0f);
    car = new PlayerCar(firstPos,hitNumCounter);
 
 
}

Player::~Player()
{
    SAFE_DELETE(hitNumCounter);
}

void Player::Update()
{
    car->Update();
    if (checkPoint->IsTransitCheckPoint(transitCPCount, car->GetHitCheckExamineInfo()))
    {
        transitCPCount++;
    }
    if (UserInput::GetInputState(Space) == Push)
    {
        ItemArgumentCarInfo itemArgumentInfo;
        itemArgumentInfo.SetCarInfo(car);
        
    }
    hitNumCounter->Update(car->GetHitCheckExamineInfo().pos);
}

PlayerRelatedInfo Player::GetRelatedInfo()
{
    PlayerRelatedInfo info = {};
    info.accelPower = car->GetTotalAccelPower();
    info.accelPowerParcent = car->GetTotalAccelPowerPercent();
    info.isReverseDrive = reverse;
    info.lap = checkPoint->GetGoalCount(transitCPCount);
    info.transitCount = transitCPCount;
    info.rank = rank;
    info.hitCoinCount = hitNumCounter->GetHitObjecctNum(ObjectTag::coin);
    info.damageObjHitCount = hitNumCounter->GetHitObjecctNum(ObjectTag::damageObject);
    printfDx("hitCoin%d\n", info.hitCoinCount);
    info.objInfo = car->GetCarPosAndDir();
    info.isAlive = car->GetAliveFlag();
    return info;
}

ObjInfo Player::GetPlayerPosAndDir()
{
    return car->GetCarPosAndDir();
}