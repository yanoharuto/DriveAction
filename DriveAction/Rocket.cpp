#include "Rocket.h"
#include "EffekseerForDXLib.h"
Rocket::Rocket(ItemArgumentCarInfo carInfo, int modelResourceHandle)
{
    position = carInfo.position;
    position = VAdd(position, VScale(carInfo.direction,-20));
    modelHandle = MV1DuplicateModel(modelResourceHandle);
    MV1SetScale(modelHandle,VGet(setSize,setSize,setSize));
    tag = ObjectTag::damageObject;
    bouncePower = setBouncePower;
    radius = setRadius;
    effectResource=LoadEffekseerEffect("data/effect/bomb.efkefc",1.0f);
    onGround = false;
}

Rocket::~Rocket()
{
    DeleteEffekseerEffect(effectResource);
}

void Rocket::Update(float deltaTime)
{
    if (!onGround)
    {
        position.y -= fallingSpeed * deltaTime;
        MV1SetPosition(modelHandle, position);
        fallingSpeed += fallingSpeed * gravityPower * deltaTime;
    }
    else
    {
        if (!IsEffekseer3DEffectPlaying(playEffect))
        {
            aliveFlag = false;
        }
    }
}

void Rocket::ConflictProccess()
{
    onGround = true;
    playEffect = PlayEffekseer3DEffect(effectResource);
    SetPosPlayingEffekseer3DEffect(playEffect, position.x, position.y, position.z);
}
