#pragma once
#include "Item.h"
#include "CpuCarMode.h"
#include "DxLib.h"
#include "Actor.h"
#include "Wheels.h"
#include "CarNeighborhoodExamineInfo.h"
#include "CarParamater.h"
#include "InputDirection.h"
#include "ItemInfo.h"
#include "AutoDriveInfo.h"
#include "HitCheckExamineObjectInfo.h"
#include "ObjPosAndDir.h"
#include "Timer.h"
/// <summary>
/// �Ԃ̉����Ƃ������Ƃ������B�ǂ̌����ɉ������邩�Ƃ���wheels����Ƃ��Ă����
/// </summary>
class Car abstract :public Actor
{

public:
	Car();
	/// <summary>
	/// �����ʒu����p�Ƃ�
	/// </summary>
	/// <param name="firstPos"></param>
	/// <param name="firstDir"></param>
	/// <param name="destinationPos"></param>
	/// <param name="soundPlayer"></param>
	Car(CarInfomation param);
    virtual ~Car();
	/// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	virtual void Update(){};
	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="conflictInfo">�Ԃ��������I�u�W�F�N�g�̏��</param>
	virtual void ConflictProccess(ConflictExamineResultInfo conflictInfo)override;
	/// <summary>
	/// ���̑��x�͍ő呬�x�̉����Ȃ̂������o����
	/// </summary>
	/// <returns></returns>
	float GetTotalAccelPowerPercent();
	/// <summary>
	/// ���̑��x
	/// </summary>
	/// <returns></returns>
	float GetTotalAccelPower();
	/// <summary>
	/// �����^�]
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="outsideHitFlag"></param>
	void AutoDrive();
	/// <summary>
    /// �J�������ɓn����������Ԃ�
    /// </summary>
	/// <returns></returns>
	ObjInfo GetCarPosAndDir();
	/// <summary>
	/// �ړ�����O�̃|�W�V������n��
	/// </summary>
	/// <returns></returns>
	HitCheckExamineObjectInfo GetHitCheckExamineInfo() override;
	/// <summary>
	/// ����
	/// </summary>
	/// <param name="deltaTime"></param>
	void UpDown();
protected:
	/// <summary>
	/// ���ʍX�V
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="destinationPos"></param>
	/// <param name="itemInfo"></param>
	void CommonUpdate();

	/// <summary>
	/// �Ԃ��Ԃ��������̊֐�
	/// </summary>
	/// <param name="conflictObjPos">�Ԃ������I�u�W�F�N�g�̈ʒu</param>
	/// <param name="conflictObjRad">�Ԃ������I�u�W�F�N�g�̔��a</param>
	virtual void ConflictReaction(const ConflictExamineResultInfo conflictInfo);
	/// <summary>
	/// �Ԃ��_���[�W����̂��镨�̂ɂԂ��������̊֐�
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="conflictInfo"></param>
	virtual void DamageReaction(const ConflictExamineResultInfo conflictInfo);
	/// <summary>
	/// ��ɎԂ��U�����󂯂���ɖ��G���Ԃ���������֐�
	/// </summary>
	/// <param name="conflictObjPos">�Ԃ������I�u�W�F�N�g�̈ʒu</param>
	/// <param name="conflictObjRad">�Ԃ������I�u�W�F�N�g�̔��a</param>
	virtual void PostDamageProccess();
	/// <summary>
	/// �i�ޕ����Ƒ������X�V����
	/// </summary>
	/// <param name"deltaTime">�o�ߎ���</param>
	/// <param name="accelVec">���̍X�V�܂łɐi�ޕ����Ƒ���</param>
	void UpdateVelocity(const VECTOR accelVec);
	/// <summary>
	/// model�̕`��ꏊ���X�V
	/// </summary>
	void UpdateMV1Pos() override;
	/// <summary>
	/// �Ԃ���]������
	/// </summary>
	void ModelSetMatrix() override;
	/// <summary>
	/// ���̃t���[���̊Ԃɐi�ޗʂ��o��
	/// </summary>
	/// <param name="handleDir">���͂��ꂽ����</param>
	/// <param name="outsideHitFlag">�R�[�X�̊O�ɂ��邩</param>
	/// <param name="deltaTime">�o�ߎ���</param>
	/// <param name="soundPlayer">�����o�����</param>
	/// <returns>�i�ޗ�</returns>
	VECTOR GetAccelVec(InputInfo inputDir);
	/// <summary>
	/// �^�]���ɂȂ鉹���Đ�����
	/// </summary>
	/// <param name="inputDir"></param>
	/// <param name="soundPlayer"></param>
	void PlayDriveSound(InputInfo inputDir);
	/// <summary>
	/// �Ԃ��������̌��ʉ���炷
	/// </summary>
	void PlayConflictSound();
	/// <summary>
	/// �Ԃ��������̃G�t�F�N�g���o��
	/// </summary>
	void PlayConflictEffect();
	/// <summary>
	/// �^�C���ɓn�����̏�����
	/// </summary>
	void InitWheelArgumentCarInfo();

	//�Ԃ̃p�����[�^�[
	CarInfomation carParam;

	//�����Ă���Ƃ��ɏo��G�t�F�N�g
	int runEffect = -1;
	//�Ԃ��������ɏo�Ă���G�t�F�N�g
	int conflictEffect = -1;
	//�Ȃ������肷��Ƃ��ɌX�����x
	const float twistZRotaSpeed = 1.7f * RAGE;
	//�ő�X���x
	const float twistZMaxRota = 27.0f * RAGE;
	//�c�ɉ�]����
	float twistZRota = 0.0f;
	//����
	float accelPower = 0;
	//�ŏ���Y���W
	float firstPosY = 0;
	//�R�T�C���Ɏg��
	float cosValue = 0;
	//cosValue�ɖ��񑫂�
	float cosAddValue = 0.05f;
	//�㉺�ɓ������x
	float updownSpeed = 2.0f;
	//�_���[�W���󂯂����̑���s�\����
	float damageReactionTime = -1.0f;
	//model�̂�������
	float modelSize = 1.0f;
	//�ړI�n�Ɍ������Ƃ��ɋȂ��邩���f����
	float turnProccesAngularLine = 5.0f;
	//�`�F�b�N�|�C���g�ɓ������Ă邩
	bool isGoalConflict = false;
	//�n�ʂɍ~��Ă��邩
	bool isOnGround = true;
	//�_���[�W
	bool isDamage = false;
	//����ȉ��̑��x�ɂȂ��Ă���accelPower��0�ɂ����
	static const float stopAccelLine;
	// �Ȃɂ����Ȃ����̌���.
	static const float defaultDecel;
	// �u���[�L���̌���.
	static const float breakDecel;
	// �O���b�v�̌���.
	static const float gripDecel;
	// ��Q���ɂԂ������Ƃ��̌�����.
	static const float colideDecel;
	//�~��鑬�x
	static const float fallSpeed;
	//�_���[�W���󂯂����̑���s�\���Ԃ̍��v
	static const float setDamageReactionTime;
	//���̃G�t�F�N�g
	static const std::string smokeEffectResource;
	//�Ԃ��������̃G�t�F�N�g
	static const std::string conflictEffectResource;
	//���̃G�t�F�N�g
	static const std::string windEffectResource;
	//�~�܂������̌��ʉ�
	static const std::string breakeSEPass;
	//�Ԃ��������̌��ʉ�
	static const std::string carClashSEPass;
	//�N���N�V�����̌��ʉ�
	static const std::string carHornSEPass;
	//�^�]���̌��ʉ�
	static const std::string drivingSEPass;
	//�_���[�W���󂯂���̖��G����
	Timer* damageCoolTimer;
	//�^�C��
	Wheels* wheels;
	//�Ԃ��������̂Ƃ̕���
	VECTOR collVec = {};
	//�ЂƂO�̃|�W�V����
	VECTOR prevPos = {};
	//�^�C���ɓn���������
	WheelArgumentCarInfo wheelArgumentCarInfo = {};
	AutoDriveInfo autoDriveP = {};
};
