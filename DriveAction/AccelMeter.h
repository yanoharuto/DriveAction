#pragma once
#include <string>
#include "StringUI.h"
#include "UI.h"
#define TIMER_FONT_NUM 10
/// <summary>
/// �v���C���[�̑����̃��[�^�[
/// </summary>
class AccelMeter:public UI
{
public:
    /// <summary>
    /// �v���C���[�̑����̃��[�^�[
    /// </summary>
    AccelMeter();
    ~AccelMeter();
    /// <summary>
    /// ���[�^�[�̐j�̍X�V
    /// </summary>
    /// <param name="accelPower"></param>
    void Update(float accelPower,float accelPowerParcent);
    /// <summary>
    /// ���[�^�[�Ɛj�̕`��
    /// </summary>
    void Draw();
private:
    //�@�`�悷��摜�̃A�h���X
    std::string speedMeterPass = "data/play/meter.png";
    //�`�悷��摜�̃A�h���X
    std::string meterAllowPass = "data/play/MeterAllow.png";
    std::string timerFont = "data/timerFont.png";

    float accelPower;
    //����
    int numberDigits = 0;


    // �j�̃f�[�^
    UIData allowPngData;
    int timerGraphHandle[TIMER_FONT_NUM];
    //�j�̉�]
    float allowRota;
    
    //�摜�̑傫��
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

