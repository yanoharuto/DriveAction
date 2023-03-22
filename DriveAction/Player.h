#pragma once
#include "Racer.h"
#include "PlayerCar.h"
#include "PlayerRelatedInfo.h"
#include "ObjPosAndDir.h"
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
    Player(VECTOR firstPos);
    ~Player();
    /// <summary>
    /// �v���C���[�̍X�V����
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <param name="outsideHitFlag"></param>
    /// <param name="damageObjGene"></param>
    void Update(float deltaTime)override;
    /// <summary>
    /// �v���C���[�̎��ӏ���Ԃ�
    /// </summary>
    /// <returns></returns>
    PlayerRelatedInfo GetRelatedInfo();
    /// <summary>
    /// �J�����ɓn����������Ԃ�
    /// </summary>
    /// <returns></returns>
    ObjInfo GetPlayerPosAndDir();
private:
    std::string rouletteSE = "rourette.mp3";
};

