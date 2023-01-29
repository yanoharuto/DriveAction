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
    // �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
    DeleteEffekseerEffect(effekseerModelHandle);
}

void AccelerationFloor::Update()
{
}

void AccelerationFloor::Draw()
{
}