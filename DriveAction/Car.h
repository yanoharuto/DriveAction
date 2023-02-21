#pragma once
#include "Item.h"
#include "CpuCarMode.h"
#include "DxLib.h"
#include "Actor.h"
#include "Wheels.h"
#include "CarNeighborhoodExamineInfo.h"
#include "NeighborhoodInfo.h"
#include "InputDirection.h"
#include "ItemInfo.h"
#include "SoundPlayer.h"
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
	Car(VECTOR firstPos,VECTOR firstDir,VECTOR destinationPos,int duplicateModelHandle);
    virtual ~Car();
	/// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	virtual void Update(const float deltaTime, const bool outsideHitFlag,ItemInfo itemInfo){};
	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="conflictInfo">�Ԃ��������I�u�W�F�N�g�̏��</param>
	void ConflictProccess(float deltaTime, const ConflictExamineResultInfo conflictInfo);
	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw();
	/// <summary>
	/// �A�C�e���ɓn�����������o��
	/// </summary>
	/// <returns></returns>
	ItemArgumentCarInfo GetItemArgumentInfo();
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
	void AutoDrive(const float deltaTime, const bool outsideHitFlag, ItemInfo itemInfo);
	void CourceOutProccess(VECTOR lastCheckPos, VECTOR lastCheckDir);
protected:
	/// <summary>
	/// �A�C�e���̌��ʂ��󂯎��
	/// </summary>
	/// <param name="item"></param>
	/// <param name="deltaTime"></param>
	void RecieveItemEffecacy(ItemInfo itemInfo, float deltaTime);
	/// <summary>
	/// �Ԃ��Ԃ��������̊֐�
	/// </summary>
	/// <param name="conflictObjPos">�Ԃ������I�u�W�F�N�g�̈ʒu</param>
	/// <param name="conflictObjRad">�Ԃ������I�u�W�F�N�g�̔��a</param>
	void ConflictReaction(float deltaTime, const ConflictExamineResultInfo conflictInfo);
	/// <summary>
	/// �Ԃ��U�����󂯂���֐�
	/// </summary>
	/// <param name="conflictObjPos">�Ԃ������I�u�W�F�N�g�̈ʒu</param>
	/// <param name="conflictObjRad">�Ԃ������I�u�W�F�N�g�̔��a</param>
	void DamageReaction(float deltaTime);
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
	/// �^�]������Ԃ�
	/// </summary>
	/// <returns></returns>
	InputInfo GetAutoDriveDirection();
	/// <summary>
	/// ���̃t���[���̊Ԃɐi�ޗʂ��o��
	/// </summary>
	/// <param name="handleDir">���͂��ꂽ����</param>
	/// <param name="outsideHitFlag">�R�[�X�̊O�ɂ��邩</param>
	/// <param name="deltaTime">�o�ߎ���</param>
	/// <param name="soundPlayer">�����o�����</param>
	/// <returns>�i�ޗ�</returns>
	VECTOR GetAccelVec(InputInfo inputDir, bool outsideHitFlag, float deltaTime);
	/// <summary>
	/// �^�]���ɂȂ鉹���Đ�����
	/// </summary>
	/// <param name="inputDir"></param>
	/// <param name="soundPlayer"></param>
	void PlayDriveSound(InputInfo inputDir);
	/// <summary>
	/// �^�C���ɓn�����̏�����
	/// </summary>
	void InitWheelArgumentCarInfo();
	/// <summary>
	/// ����
	/// </summary>
	/// <param name="deltaTime"></param>
	void Down(float deltaTime);

	//����
	float accelPower = 0;
	//�O�I�v���ɂ�鑬��
	float forcePower = 0;
	//�Ԃ��������̒��˕Ԃ��
	float conflictObjBouncePower;
	int brekeCount = 0;
	//�_���[�W���󂯂����̑���s�\����
	float damageReactionTime = -1.0f;
	//�`�F�b�N�|�C���g�ɓ������Ă邩
	bool isGoalConflict = false;
	//�n�ʂɍ~��Ă��邩
	bool isOnGround = true;
	//�_���[�W
	bool isDamage = false;
	//�R�[�X�A�E�g��������
	bool isCourceOutProccessing = false;
	//�^�C��
	Wheels* wheels;
	//�ړI�n
	VECTOR destinationPos = {};
	//�R�[�X�A�E�g�����Ƃ��̖ړI�n
	VECTOR prevDestinationPos = {};
	//���̊p�x
	VECTOR destinationDir = {};
	//�R�[�X�A�E�g�����Ƃ��Ɍ����Ȃ���΂����Ȃ�����
	VECTOR prevDestinationDir = {};
	//�Ԃ��������̂Ƃ̕���
	VECTOR conflictVec = {};
	//�^�C���ɓn���������
	WheelArgumentCarInfo wheelArgumentCarInfo = {};
};
