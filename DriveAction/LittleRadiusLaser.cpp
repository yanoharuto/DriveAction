#include "LittleRadiusLaser.h"
//��]���x
const float LittleRadiusLaser::rotaSpeed = 4.0f;
//���[�U�[�̒��S����̋���
const InitParam LittleRadiusLaser::initParam =
{
    "LittleRadiusLaser.efkefc",
    120.0f,
    30.0f,
    20.0f,
    0.325f,
};
LittleRadiusLaser::LittleRadiusLaser(FiringObjOwner* owner)
    :RotatingLasers(owner,initParam)
{
}

LittleRadiusLaser::~LittleRadiusLaser()
{
}

void LittleRadiusLaser::Update()
{
    RotateLaser(initParam.laserEffectPass,rotaSpeed,initParam.laserRange);
    SetLaserTrack();
}
