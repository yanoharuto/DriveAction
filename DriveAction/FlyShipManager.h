#pragma once
#include <list>
#include "ObjectObserver.h"
class Timer;
class BomberFlyShip;
class CircleLaserFlyShip;
class UpDownLaserFlyShip;
class RacerManager;
/// <summary>
/// �G�@�̃}�l�[�W���[
/// </summary>
class FlyShipManager
{
public:
    /// <summary>
    /// �G�@�̏���������
    /// </summary>
    FlyShipManager(RacerManager* racerManager);

    ~FlyShipManager();
    /// <summary>
    /// �G�@�����̍X�V
    /// </summary>
    /// <param name="infoCenter"></param>
    void Update();
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();
    /// <summary>
    /// �����@�̏�����
    /// </summary>
    /// <param name="infoCenter"></param>
    void BomberShipInit();
    /// <summary>
    /// ���[�U�[�V�b�v�̏�����
    /// </summary>
    /// <param name="infoCenter"></param>
    void LaserShipInit();
private:
    //�����@�̃��X�g
    std::list<BomberFlyShip*>bombList;
    //�~��ɐw�`�����G�@�̃��X�g
    std::list<CircleLaserFlyShip*>circleFlyshipList;
    //�㉺�Ɉړ����Ȃ��烌�[�U�[�𔭎˂���G�@�̃��X�g
    std::list<UpDownLaserFlyShip*>updownFlyShipList;
    //�����@�ė��p�̃^�C�}�[
    Timer* bomberFlyShipGoTimer;
    //�v���C���[�̈ʒu
    ObjectObserver* playerObserver;
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
    //���[�U�[�����Ă���G�̍��W
    const std::string enemyPosPass = "data/stageMap_enemyPos.csv";    
};