#pragma once
#include <string>
#include "StringUI.h"
#include "UI.h"
#define TIMER_FONT_NUM 10
/// <summary>
/// プレイヤーの速さのメーター
/// </summary>
class AccelMeter:public UI
{
public:
    /// <summary>
    /// プレイヤーの速さのメーター
    /// </summary>
    AccelMeter();
    ~AccelMeter();
    /// <summary>
    /// メーターの針の更新
    /// </summary>
    /// <param name="accelPower"></param>
    void Update(float accelPower,float accelPowerParcent);
    /// <summary>
    /// メーターと針の描画
    /// </summary>
    void Draw();
private:
    //　描画する画像のアドレス
    std::string speedMeterPass = "data/play/meter.png";
    //描画する画像のアドレス
    std::string meterAllowPass = "data/play/MeterAllow.png";
    std::string timerFont = "data/timerFont.png";

    float accelPower;
    //桁数
    int numberDigits = 0;


    // 針のデータ
    UIData allowPngData;
    int timerGraphHandle[TIMER_FONT_NUM];
    //針の回転
    float allowRota;
    
    //画像の大きさ
    const float size = 0.55f;
    int eraseFontPosiLength = -1;
    const int eraseFontDecLength = 2;
    const float timerFontLoadSize = 80.0f;
    const float timerFontBigSize = 1.0f;
    const float timerFontSmaleSize = 0.65f;
    const float meterSize = 0.4f;
    const float firstRota = -90.0f;
    const float maxSpeed = 180.0f;
};

