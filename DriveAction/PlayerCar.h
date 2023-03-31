#pragma once
#include "Car.h"
#include "AssetManager.h"
#include "SphereCollider.h"
#include "HitNumCounter.h"
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
	PlayerCar(VECTOR firstPos,HitNumCounter* counter);
	///�f�X�g���N�^
    ~PlayerCar();
    /// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	void Update() override;

private:
	//���͂ɂ���đ��������ς���
	void SetInputDir();
	//����
	const float setFirstPosY = 6.0f;
	const float setDamageCoolTime = 1.5f;
	//�������蔻��
	SphereCollider* collider;
	static const CarInfomation setCarParam;
};