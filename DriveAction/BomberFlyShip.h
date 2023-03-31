#pragma once
#include "FlyShip.h"
class BomberFlyShip :
    public FlyShip
{
public:
    BomberFlyShip();
    BomberFlyShip(VECTOR setFirstPos, VECTOR setDestinationPos);
    ~BomberFlyShip();
    void Update() override;
    void Init(VECTOR newPosition, VECTOR newDestinationPos)override;
private:
    float coolTime;
    static const int SEVolume;
    static const std::string flightSE;
    //����Y���W
    static const float setFirstPosY;
    //����
    static const float speed;
    //model�̑傫��
    static const float modelSize;
    //��
    static const float setRadius;
    //�������ԁ@���e���˃N�[���^�C���@�ő卂�x�@�㏸���x
    static const FlyShipArgumentInfo setFlyShipParam;
};

