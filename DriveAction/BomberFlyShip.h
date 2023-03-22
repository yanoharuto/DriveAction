#pragma once
#include "FlyShip.h"

class BomberFlyShip :
    public FlyShip
{
public:
    BomberFlyShip();
    BomberFlyShip(VECTOR setFirstPos, VECTOR setDestinationPos);
    ~BomberFlyShip();
    void Update(const float deltaTime) override;
private:
    //����Y���W
    static const float setFirstPosY;
    //����
    static const float speed;
    //model�̑傫��
    static const float modelSize;
    //��
    static const float setRadius;
    //���e�̌�������
    int bomberCount = 0;
    //�������ԁ@���e���˃N�[���^�C���@�ő卂�x�@�㏸���x
    static const FlyShipArgumentInfo setFlyShipParam;
};

