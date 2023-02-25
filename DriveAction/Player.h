#pragma once
#include "Racer.h"
#include "PlayerCar.h"
#include "PlayerRelatedInfo.h"
#include "PlaySceneCamaeraArgumentInfo.h"
/// <summary>
/// �v���C���[�̎Ԃ�A�C�e���̏������Ăяo��
/// </summary>
class Player final:
    public Racer 
{
public:
    Player();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="circuitData"></param>
    /// <param name="firstPos"></param>
    /// <param name="firstDir"></param>
    Player(VECTOR firstPos, int duplicateModel);
    ~Player();
    /// <summary>
    /// �v���C���[�̍X�V����
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObjGene"></param>
    void Update(float deltaTime, bool outsideHitFlag, DamageObjectGenerator* damageObjGene)override;
    /// <summary>
    /// �v���C���[�̎��ӏ���Ԃ�
    /// </summary>
    /// <returns></returns>
    PlayerRelatedInfo GetRelatedInfo();
    /// <summary>
    /// �J�����ɓn����������Ԃ�
    /// </summary>
    /// <returns></returns>
    PlaySceneCameraArgumentInfo GetCameraArgumentInfo();
private:
    PlayerCar* playerCar = nullptr;
    std::string rouletteSE = "rourette.mp3";
    float setHP = 100;
};

