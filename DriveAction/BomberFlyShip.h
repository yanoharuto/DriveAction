#pragma once
#include "FlyShip.h"
#include <string>
struct FlyShipArgumentInfo;
class Timer;
/// <summary>
/// �����@
/// </summary>
class BomberFlyShip :
    public FlyShip
{
public:
    /// <summary>
    /// �����@
    /// </summary>
    /// <param name="setFirstPos">�o���ʒu</param>
    /// <param name="setDestinationPos">�ړI�n</param>
    BomberFlyShip(VECTOR setFirstPos, VECTOR setDestinationPos);
    /// <summary>
    /// ���e�𗎂Ƃ��Ȃ���i��
    /// </summary>
    void Update() override;
private:
    Timer* timer;
    static const int SEVolume;
    static const std::string flightSE;
    //����
    static const float speed;
    //�������ԁ@���e���˃N�[���^�C���@�ő卂�x�@�㏸���x
    static const FlyShipArgumentInfo setFlyShipParam;
};

