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
    effekseerModelHandle = LoadEffekseerEffect("data/effect/accelationFloor.efkefc",5.0f);
    playingEffect = PlayEffekseer3DEffect(effekseerModelHandle);
    OriginalMath math;
    VECTOR vecX = VGet(direction.x, 0, 0);
    VECTOR vecZ = VGet(0, 0, direction.z);

    float degreeY = math.GetDegreeMisalignment(vecX, vecZ);
    degreeY = VCross(vecX, vecZ).y > 0 ? degreeY : -degreeY;
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
