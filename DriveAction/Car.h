#pragma once
#include "DxLib.h"
#include "Actor.h"
#include "Wheels.h"
#include "CarNeighborhoodExamineInfo.h"
#include "NeighborhoodInfo.h"
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
	virtual void Update(const float deltaTime, const bool outsideHitFlag,NeighborhoodInfo neighInfo) {};
	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="conflictInfo">�Ԃ��������I�u�W�F�N�g�̏��</param>
	void ConflictProcess(float deltaTime, const ConflictExamineResultInfo conflictInfo) override;
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// ���ӂ𒲂ׂĂ��炤���߂ɓn��
	/// </summary>
	/// <returns></returns>
	CarNeighborhoodExamineInfo GetNeighExamineInfo();
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
	void AutoDrive(const float deltaTime, const bool outsideHitFlag,NeighborhoodInfo neighInfo);
	/// <summary>
	/// �^�]������Ԃ�
	/// </summary>
	/// <returns></returns>
	HandleDirection GetHandleDir(NeighborhoodInfo neighInfo);
	/// <summary>
	/// ���̃t���[���̊Ԃɐi�ޗʂ��o��
	/// </summary>
	/// <param name="handleDir">�i�s����</param>
	/// <param name="outsideHitFlag">�O��</param>
	/// <param name="deltaTime">�o�ߎ���</param>
	/// <returns>�i�ޗ�</returns>
	virtual VECTOR GetAccelVec(HandleDirection handleDir, bool outsideHitFlag, float deltaTime);
	/// <summary>
	/// ���ӏ�񂩂�Ȃ�����ɉe����^����
	/// </summary>
	/// <param name="neighInfo"></param>
	/// <returns></returns>
	float GetNeighSize(NeighborhoodInfo neighInfo);

	// �ÓI�萔.
	const float accelSpeed = 12.4f;					// �ʏ�̉���.
	const float maxSpeed = 200.0f;					// �ō����x.
	const float defaultDecel = 0.04f;			// �Ȃɂ����Ȃ����̌���.
	const float breakDecel = 0.97f;				// �u���[�L���̌���.
	const float gripDecel = 0.125f;				// �O���b�v�̌���.
	const float gripPower = 0.06f;				// �O���b�v��.
	const float maxGripPower = 1.2f;				// �ő�O���b�v��.
	const float colideDecel = 0.2f;	    // ��Q���ɂԂ������Ƃ��̌�����.
	const float outsideHitDecel = 0.4f;   //�R�[�X�̊O���ɗ������̌���
	const float radiusValue = 3.0f; //�Ԃ̕�
	const float turnProccesLine = 9.0f;//�ړI�n�Ɍ������Ƃ��ɋȂ��邩���f����
	const float examineRange = 150.0f;
	float accelPower = 0;             //�v�Z���ʂɂ���ďo�鑬��
	int effectResourceHandle = -1;//���̃G�t�F�N�g
	bool isStraightDash;//�܂������i��ł��邩�ǂ���
	Wheels* wheels;//�^�C��
	VECTOR destinationPos;
};

