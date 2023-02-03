#pragma once
#include <string>
#include "UI.h"
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
    void Update(float accelPower);
    /// <summary>
    /// ���[�^�[�Ɛj�̕`��
    /// </summary>
    void Draw();
private:
    //�@�`�悷��摜�̃A�h���X
    std::string speedMeterAddress = "data/play/speedMeter.png";
    //�`�悷��摜�̃A�h���X
    std::string meterAllowAddress = "data/play/MeterAllow.png";
    
    // �j�̃f�[�^
    UIData allowPngData;
    //�j�̉�]
    float allowRota;
    //�摜�̑傫��
    const float size = 0.85f;
};

