#pragma once
#include "FlyShip.h"
#include "PlayerRelatedInfo.h"
/// <summary>
/// ���[�U�[���o����s�D
/// </summary>
class LaserFlyShip abstract:
    public FlyShip
{
public:
    /// <summary>
    /// ���[�U�[���o���D
    /// </summary>
    LaserFlyShip();
    /// <summary>
    /// ������ �ړI�n�̕��Ɍ�������
    /// </summary>
    /// <param name="firstPos"></param>
    /// <param name="setDestinationPos"></param>
    LaserFlyShip(VECTOR firstPos, VECTOR setDestinationPos);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~LaserFlyShip();
    /// <summary>
    /// �J�����ɉf��Ȃ����Ȃ�G�t�F�N�g������
    /// </summary>
    /// <param name="playerInfo"></param>
    virtual void Init(PlayerRelatedInfo playerInfo);
    /// <summary>
    /// ���[�U�[���Ǝ�
    /// </summary>
    virtual void GenerateLaser() = 0;
protected:
    //�����ʒuY
    float firstPosY;
};
