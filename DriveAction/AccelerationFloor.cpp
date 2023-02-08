#include "AccelerationFloor.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
AccelerationFloor::AccelerationFloor()
{

}

AccelerationFloor::AccelerationFloor(VECTOR pos, VECTOR dir)
{
    position = pos;
    direction = dir;
    tag = ObjectTag::acelerationFloor;
    radius = setRadius;
    effekseerModelHandle = LoadEffekseerEffect("data/effect/accelationFloor.efkefc",setScale);
    playingEffect = PlayEffekseer3DEffect(effekseerModelHandle);
    OriginalMath math;
    float degreeY = dir.y;
    degreeY *= RAGE;
    SetRotationPlayingEffekseer3DEffect(playingEffect, 0,degreeY,0);
    SetPosPlayingEffekseer3DEffect(playingEffect,position.x,position.y,position.z);
}

AccelerationFloor::~AccelerationFloor()
{
    // エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
    DeleteEffekseerEffect(effekseerModelHandle);
}

void AccelerationFloor::Update(const float deltaTime)
{
}
void AccelerationFloor::Draw()
{
}
