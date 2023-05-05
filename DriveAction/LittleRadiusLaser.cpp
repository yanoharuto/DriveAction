#include "LittleRadiusLaser.h"
#include "EffectManager.h"
//回転速度
const float LittleRadiusLaser::rotaSpeed = 4.0f;
//レーザーの中心からの距離
const InitParam LittleRadiusLaser::initParam =
{
    EffectKind::littleRadiusLaser,
    Init::InitObjKind::littleRadiusLaser,
    120.0f,
    30.0f,
    20.0f,
    0.325f,
};
LittleRadiusLaser::LittleRadiusLaser(ObjectObserver* setObserver)
    :RotatingLasers(initParam, setObserver)
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
