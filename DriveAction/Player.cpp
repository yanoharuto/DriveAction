#include "Player.h"
#include"Utility.h"
Player::Player()
{
}

Player::Player(VECTOR firstPos, int duplicateModel)
    :Racer()
{
    playerCar = new PlayerCar(firstPos,checkPoint->GetDir(), checkPoint->GetPos(), duplicateModel);
    SetCarPointer(playerCar);
    SoundPlayer::LoadSound(rouletteSE);
}

Player::~Player()
{
}

void Player::Update(float deltaTime, bool outsideHitFlag, DamageObjectGenerator* damageObjGene)
{
    ItemInfo itemInfo = itemHolder->GetItemInfo();
    if (checkPoint->GetGoalCount() == 2)
    {
        car->AutoDrive(deltaTime, outsideHitFlag, itemInfo); 
    }
    else
    {
        car->Update(deltaTime, outsideHitFlag, itemInfo);
    }
    CommonUpdate(deltaTime,outsideHitFlag,damageObjGene);
    int inputKey = GetJoypadInputState(DX_INPUT_KEY);
    if ((inputKey & PAD_INPUT_10 || itemInfo.itemSituation == ItemUseSituation::Useing) && itemInfo.itemTag != non)
    {
        itemHolder->UseItem(car->GetItemArgumentInfo());
    }
    else if (itemInfo.itemTag == roulette)
    {
        if (!SoundPlayer::IsPlaySound(rouletteSE))
        {
            SoundPlayer::Play2DSE(rouletteSE);
        }
    }
    else
    {
        SoundPlayer::StopSound(rouletteSE);
    }
}

PlayerRelatedInfo Player::GetRelatedInfo()
{
    PlayerRelatedInfo info = {};
    info.accelPower = car->GetTotalAccelPower();
    info.accelPowerParcent = car->GetTotalAccelPowerPercent();
    info.reverse = reverse;
    info.itemTag = itemHolder->GetItemInfo().itemTag;
    info.lap = checkPoint->GetGoalCount();
    info.rank = rank;
    
    return info;
}

PlaySceneCameraArgumentInfo Player::GetCameraArgumentInfo()
{
    PlaySceneCameraArgumentInfo argumentInfo = {};
    argumentInfo.dir = playerCar->GetDir();
    argumentInfo.pos = playerCar->GetPos();
    return argumentInfo;
}