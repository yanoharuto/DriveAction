#include "AccelMeter.h"
#include "DxLib.h"
#include "Utility.h"
#include "OriginalMath.h"
AccelMeter::AccelMeter()
{
    LoadDivGraph(timerFont.c_str(), TIMER_FONT_NUM, TIMER_FONT_NUM, 1, timerFontLoadSize, 100, timerGraphHandle);
    uiData.x = UI_SCREEN_WIDTH * 17.0f;
    uiData.y = UI_SCREEN_HEIGHT * 16.0f;
    uiData.dataHandle = LoadGraph(speedMeterPass.c_str());
    allowPngData.x = UI_SCREEN_WIDTH * 18.5f;
    allowPngData.y = UI_SCREEN_HEIGHT * 16;
    allowPngData.dataHandle = LoadGraph(meterAllowPass.c_str());
    
    allowRota = 0;
}

AccelMeter::~AccelMeter()
{
    DeleteGraph(allowPngData.dataHandle);
    DeleteGraph(uiData.dataHandle);
    
}

void AccelMeter::Update(float getAccelPower,float accelPowerParcent)
{
    accelPower = getAccelPower;
    numberDigits = 0;

    allowRota =(accelPowerParcent / 100 * 180 + firstRota) * RAGE ;
}

void AccelMeter::Draw()
{
    DrawRotaGraph(uiData.x, uiData.y,meterSize,0, uiData.dataHandle, true,false,false);
    DrawRotaGraph(allowPngData.x, allowPngData.y, size, allowRota, allowPngData.dataHandle, true, false, false);
    float fontSize = timerFontBigSize;
    float decX = uiData.x;
    for (int i = 0; i < numberDigits; i++)
    {
        decX+=fontSize;
        DrawRotaGraph(decX, uiData.y, fontSize, 0, timerGraphHandle[i], true, false, false);
    }
    fontSize = timerFontSmaleSize;
   
}