#pragma once
#include "Car.h"
class SphereCollider;
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
	PlayerCar(VECTOR firstPos);
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

	static const CarInfomation setCarParam;
};