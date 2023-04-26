#pragma once
#include <list>
#include "FlyShip.h"
#include "PlayerInformationCenter.h"
#include "Timer.h"
#include "BomberFlyShip.h"
#include "CircleLaserFlyShip.h"
#include "UpDownLaserFlyShip.h"
/// <summary>
/// �G�@�̃}�l�[�W���[
/// </summary>
class FlyShipManager
{
public:
    /// <summary>
    /// �G�@�̏���������
    /// </summary>
    FlyShipManager();

    ~FlyShipManager();
    /// <summary>
    /// �G�@�����̍X�V
    /// </summary>
    /// <param name="infoCenter"></param>
    void Update(PlayerInformationCenter* infoCenter);
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();
    /// <summary>
    /// �����@�̏������@�ė��p���邽�߂Ɏg���@
    /// </summary>
    /// <param name="infoCenter"></param>
    void BomberShipInit(PlayerInformationCenter* infoCenter);
    /// <summary>
    /// ���[�U�[�V�b�v�̏������@�ė��p���邽�߂Ɏg��
    /// </summary>
    /// <param name="infoCenter"></param>
    void LaserShipInit(PlayerInformationCenter* infoCenter);
private:
    //�����@�̃��X�g
    std::list<BomberFlyShip*>bombList;
    //�~��ɐw�`�����G�@�̃��X�g
    std::list<CircleLaserFlyShip*>circleFlyshipList;
    //�㉺�Ɉړ����Ȃ��烌�[�U�[�𔭎˂���G�@�̃��X�g
    std::list<UpDownLaserFlyShip*>updownFlyShipList;
    //�����@�ė��p�̃^�C�}�[
    Timer* bomberFlyShipGoTimer;
    //�����@�̏������̊Ԋu
    const float setBShipInitSpan = 5.0f;
    //�~��̓G�@�̐�
    const int circleShipNum = 6;
    //��x�ɔ��i����G�@�̐�
    const int BomberFlyShipNum = 3;
    //�����@�̏���������Ƃ��Ɏg���p�x
    const int bShipInitRandDeg = 60;
    //�����@�̏��������̃v���C���[�Ƃ̋����Ɏg��
    const float initBShipGeneratePosScale = 1000.0f;
    //�����@���m�̋���
    const float initBShipBetween = 300.0f;
    
    //�����@�̃A�h���X
    const std::string bomberModelPass = "Player/PrototypeZero.mv1";
    //model�̃A�h���X
    const std::string ufoModelPass = "Player/Rocker.mv1";
    //���[�U�[�����Ă���G�̍��W
    const std::string enemyPosPass = "data/stageMap_enemyPos.csv";
    
};