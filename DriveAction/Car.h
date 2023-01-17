#pragma once
#include "DxLib.h"
#include "Actor.h"
#include "Wheels.h"
/// <summary>
/// �Ԃ̉����Ƃ������Ƃ������B�ǂ̌����ɉ������邩�Ƃ���wheels����Ƃ��Ă����
/// </summary>
class Car :public Actor
{
public:
	Car();
	Car(VECTOR firstPos,VECTOR firstDir);
    virtual ~Car();
	/// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	virtual void Update(const float deltaTime, const bool outsideHitFlag) {};
	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="conflictInfo">�Ԃ��������I�u�W�F�N�g�̏��</param>
	void ConflictProcess(float deltaTime, const ArgumentConflictInfo conflictInfo) override;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();

protected:
	/// <summary>
	/// �Ԃ��Ԃ��������̊֐�
	/// </summary>
	/// <param name="conflictObjPos">�Ԃ������I�u�W�F�N�g�̈ʒu</param>
	/// <param name="conflictObjRad">�Ԃ������I�u�W�F�N�g�̔��a</param>
	void ConflictReaction(float deltaTime, const VECTOR conflictObjPos, const float conflictObjRad);
	/// <summary>
	/// �Ԃ��U�����󂯂���֐�
	/// </summary>
	/// <param name="conflictObjPos">�Ԃ������I�u�W�F�N�g�̈ʒu</param>
	/// <param name="conflictObjRad">�Ԃ������I�u�W�F�N�g�̔��a</param>
	void DamageReaction(const VECTOR conflictObjPos, const float conflictObjRad);
	/// <summary>
	/// �i�ޕ����Ƒ������X�V����
	/// </summary>
	/// <param name"deltaTime">�o�ߎ���</param>
	/// <param name="accelVec">���̍X�V�܂łɐi�ޕ����Ƒ���</param>
	void UpdateVelocity(const VECTOR accelVec);
	/// <summary>
	/// model�̕`��ꏊ���X�V
	/// </summary>
	void UpdateMV1Pos();
	/// <summary>
	/// �Ԃ���]������
	/// </summary>
	void ModelSetMatrix();
	/// <summary>
	/// �����^�]
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="outsideHitFlag"></param>
	void AutoDrive(const float deltaTime, const bool outsideHitFlag);
	/// <summary>
	/// �^�]������Ԃ�
	/// </summary>
	/// <returns></returns>
	HandleDirection GetHandleDir();
	/// <summary>
	/// ���̃t���[���̊Ԃɐi�ޗʂ��o��
	/// </summary>
	/// <param name="handleDir">�i�s����</param>
	/// <param name="outsideHitFlag">�O��</param>
	/// <param name="deltaTime">�o�ߎ���</param>
	/// <returns>�i�ޗ�</returns>
	virtual VECTOR GetAccelVec(HandleDirection handleDir, bool outsideHitFlag, float deltaTime);
	// �ÓI�萔.
	const float accelSpeed =27.0f;					// �ʏ�̉���.
	const float maxSpeed = 250.0f;					// �ō����x.
	const float defaultDecel = 0.04f;			// �Ȃɂ����Ȃ����̌���.
	const float breakDecel = 0.97f;				// �u���[�L���̌���.
	const float gripDecel = 0.125f;				// �O���b�v�̌���.
	const float gripPower = 0.08f;				// �O���b�v��.
	const float maxGripPower = 1.2f;				// �ő�O���b�v��.
	const float colideDecel = 0.45f;	    // ��Q���ɂԂ������Ƃ��̌�����.
	const float outsideHitDecel = 0.2f;   //�R�[�X�̊O���ɗ������̌���
	const float rage = static_cast<float>(DX_PI / 180.0f); //���W�A��
	const float radiusValue = 3.0f; //�Ԃ̕�
	float accelPower = 0;             //�v�Z���ʂɂ���ďo�鑬��
	const float turnProccesLine = 0.25f;//�ړI�n�Ɍ������Ƃ��ɋȂ��邩���f����
	Wheels* wheels;//�^�C��
	VECTOR destinationPos;
};

