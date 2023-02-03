#pragma once
#include <string>
#include "UI.h"
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
    void Update(float accelPower);
    /// <summary>
    /// メーターと針の描画
    /// </summary>
    void Draw();
private:
    //　描画する画像のアドレス
    std::string speedMeterAddress = "data/play/speedMeter.png";
    //描画する画像のアドレス
    std::string meterAllowAddress = "data/play/MeterAllow.png";
    
    // 針のデータ
    UIData allowPngData;
    //針の回転
    float allowRota;
    //画像の大きさ
    const float size = 0.85f;
};

