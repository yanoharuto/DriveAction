#pragma once
#include "Car.h"
#include "AssetManager.h"
#include "SphereCollider.h"
class Wheels;
 /// <summary>
 /// �v���C���[(��)
 /// </summary>
 class PlayerCar final: public Car
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns></returns>
	PlayerCar();
	PlayerCar(VECTOR firstPos);
	///�f�X�g���N�^
    ~PlayerCar();
    /// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	void Update(const float deltaTime, VECTOR destinationPos,ItemInfo itemInfo) override;
private:
	void PostDamageProccess(float deltaTime)override;
	void DamageReaction(const ConflictExamineResultInfo conflictInfo)override;
	//���͂ɐ����đ��������ς���
	void SetInputDir();
	//����
	const float setFirstPosY = 6.0f;
	const float setDamageCoolTime = 3.0f;
	int damageEffect[3] = { -1,-1,-1 };
	//�̗�
	int HP = 0;
	float damageCoolTime = -1.0f;
	SphereCollider* collider;
};