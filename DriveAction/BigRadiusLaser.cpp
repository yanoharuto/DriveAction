#include "BigRadiusLaser.h"
#include "EffectManager.h"
#include "EffekseerForDXLib.h"
#include "OriginalMath.h"
#include "ConflictManager.h"
#include "Utility.h"
const InitParam BigRadiusLaser::initParam =
{
    "BigRadiusLaser.efkefc",
    120.0f,
    30.0f,
    20.0f,
    1.3f
};
//‰ñ“]‘¬“x
const float BigRadiusLaser::rotaSpeed = 2.0f;

BigRadiusLaser::BigRadiusLaser(FiringObjOwner* setOwner)
    :RotatingLasers(setOwner,initParam)
{
}


void BigRadiusLaser::Update()
{
    RotateLaser(initParam.laserEffectPass,rotaSpeed, initParam.laserRange);
    SetLaserTrack();
}
