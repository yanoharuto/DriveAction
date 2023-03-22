#include "AccelerationFloor.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "EffectManager.h"
AccelerationFloor::AccelerationFloor()
{

}

AccelerationFloor::AccelerationFloor(VECTOR pos, VECTOR dir)
{
    position = pos;
    direction = dir;
    tag = ObjectTag::acelerationFloor;
    radius = setRadius;
    EffectManager::LoadEffectManager("accelationFloor.efkefc", setScale);
    playingEffect = EffectManager::GetPlayEffect3D("accelationFloor.efkefc");
    float degreeY = dir.y;
    degreeY *= RAGE;
    SetRotationPlayingEffekseer3DEffect(playingEffect, 0,degreeY,0);
    SetPosPlayingEffekseer3DEffect(playingEffect,position.x,position.y,position.z);
}

AccelerationFloor::~AccelerationFloor()
{
}

void AccelerationFloor::Update(const float deltaTime)
{
}
void AccelerationFloor::Draw()
{
}
