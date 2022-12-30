#pragma once
#include "DxLib.h"
#include "Actor.h"

class Wheels;
/// <summary>
/// �Ԃ̉����Ƃ������Ƃ������B�ǂ̌����ɉ������邩�Ƃ���wheels����Ƃ��Ă����
/// </summary>
class Car :public Actor
{
public:
	Car();
    virtual ~Car();
	/// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	virtual void Update(const float deltaTime, const bool outsideHitFlag) {};
	/// <summary>
	/// �^�C���Ǝԑ̂̕`��
	/// </summary>
	virtual void Draw();
protected:
	/// <summary>
	/// �i�ޕ����Ƒ������X�V����
	/// </summary>
	/// <param name="deltaTime">�o�ߎ���</param>
	/// <param name="accelVec">���̍X�V�܂łɐi�ޕ����Ƒ���</param>
	void UpdateVelocity(const float deltaTime, const VECTOR accelVec);
	/// <summary>
	/// model�̕`��ꏊ���X�V
	/// </summary>
	void UpdateMV1Pos();
	/// <summary>
	/// �Ԃ���]������
	/// </summary>
	void ModelSetMatrix();
	// �ÓI�萔.
	const float accelSpeed = 1.8f;					// �ʏ�̉���.
	const float maxSpeed = 180.0f;					// �ō����x.
	const float defaultDecel = -0.004f;			// �Ȃɂ����Ȃ����̌���.
	const float breakDecel = -0.075f;				// �u���[�L���̌���.
	const float gripDecel = -0.025f;				// �O���b�v�̌���.
	const float gripPower = 1.2f;				// �O���b�v��.
	const float maxGripPower = 0.4f;				// �ő�O���b�v��.
	const float colideDecel = 0.4f;	    // ��Q���ɂԂ������Ƃ��̌�����.
	const float outsideHitDecel = -0.08f;   //�R�[�X�̊O���ɗ������̌���
	const float rage = static_cast<float>(DX_PI / 180.0f); //���W�A��
	const float radiusValue = 30.0f; //�Ԃ̕�
	float accel = 0;             //�v�Z���ʂɂ���ďo�鑬��
	Wheels* wheels;//�^�C��
};

