#include "AccelMeter.h"
#include "DxLib.h"
#include "Utility.h"
#include "OriginalMath.h"
AccelMeter::AccelMeter()
{
    allowPngData.x = SCREEN_WIDTH / 13 * 9;
    allowPngData.y = SCREEN_HEIGHT / 15 * 14;
    allowPngData.dataHandle = LoadGraph(meterAllowAddress.c_str());
    uiData.x = SCREEN_WIDTH / 13 * 9;
    uiData.y = SCREEN_HEIGHT / 15 * 13;
    uiData.dataHandle = LoadGraph(speedMeterAddress.c_str());
    allowRota = 0;
}

AccelMeter::~AccelMeter()
{
    DeleteGraph(allowPngData.dataHandle);
    DeleteGraph(uiData.dataHandle);
}

void AccelMeter::Update(float accelPower)
{
    allowRota = accelPower * RAGE;
}

void AccelMeter::Draw()
{
    DrawRotaGraph(uiData.x, uiData.y,size,0, uiData.dataHandle, true,false,false);
    DrawRotaGraph(allowPngData.x, allowPngData.y, size, allowRota, allowPngData.dataHandle, true, false, false);
}
