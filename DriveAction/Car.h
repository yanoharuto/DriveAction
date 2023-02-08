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
	Car(VECTOR firstPos,VECTOR firstDir,VECTOR destinationPos,SoundPlayer* soundPlayer);
    virtual ~Car();
	/// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
	virtual void Update(const float deltaTime, const bool outsideHitFlag,ItemInfo itemInfo,SoundPlayer* soundPlayer){};
	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="conflictInfo">�Ԃ��������I�u�W�F�N�g�̏��</param>
	void ConflictProcess(float deltaTime, const ConflictExamineResultInfo conflictInfo, SoundPlayer* soundPlayer);
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
	void ConflictReaction(float deltaTime, const ConflictExamineResultInfo conflictInfo,SoundPlayer* soundPlayer);
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
	/// �����^�]
	/// </summary>
	/// <param name="deltaTime"></param>
	/// <param name="outsideHitFlag"></param>
	void AutoDrive(const float deltaTime, const bool outsideHitFlag ,ItemInfo itemInfo,SoundPlayer* soundPlayer);
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
	void PlayDriveSound(InputInfo inputDir, SoundPlayer* soundPlayer);
	/// <summary>
	/// �^�C���ɓn�����̏�����
	/// </summary>
	void InitWheelArgumentCarInfo();
	void Down(float deltaTime);
	//�`�F�b�N�|�C���g�ɒʉ߂�����
	int checkCount = 0;
	// �ʏ�̉���.
	const float accelAddSpeed = 38.4f;					
	// �ʏ�ō����x.
	const float maxAccelSpeed = 230.0f;					
	//�O�I�v���̑����̍ō����x
	const float maxAddForcePower = 100.0f;
	//�O�I�v���̑���
	const float addAccelForce = 8.0f;
	//����ȉ��̑��x�ɂȂ��Ă���accelPower��0�ɂ����
	const float stopAccelLine = 5.0f;
	// �Ȃɂ����Ȃ����̌���.
	const float defaultDecel = 0.2f;			
	// �u���[�L���̌���.
	const float breakDecel = 0.97f;				
	// �O���b�v�̌���.
	const float gripDecel = 0.54f;				
	// �O���b�v��.
	const float gripPower = 0.14f;				
	// ��Q���ɂԂ������Ƃ��̌�����.
	const float colideDecel = 0.2f;	  
	//�R�[�X�̊O���ɗ������̌���
	const float outsideHitDecel = 0.28f;          
	//�Ԃ̕�
	const float radiusValue = 3.8f;              
	//�ړI�n�Ɍ������Ƃ��ɋȂ��邩���f����
	const float turnProccesAngularLine = 5.0f;  
	//���˕Ԃ�͂̌Œ�l
	const float setBouncePower = 1.0f;
	//�~��鑬�x
	const float downSpeed = 10.8f;
	//�ŏ���Y���W
	const float firstPosY = -4.0;
	//����
	float accelPower = 0;                        
	//�O�I�v���ɂ�鑬��
	float forcePower = 0;
	//�Ԃ��������̒��˕Ԃ��
	float conflictObjBouncePower;
	//�_���[�W���󂯂����̑���s�\����
	float damageReactionTime = -1.0f;
	//�_���[�W���󂯂����̑���s�\���Ԃ̍��v
	const float setDamageReactionTime = 1.2f;
	//���̃G�t�F�N�g
	int smokeEffectResource = -1;
	//�Ԃ��������̃G�t�F�N�g
	int conflictEffectResource = -1;
	//�O�I�v���ő����Ȃ������̃G�t�F�N�g
	int accelerationEffectResource = -1;
	int accelerationPlayEffect = -1;
	int count = 0;
	//�~�܂������̌��ʉ�
	const std::string breakeSEAddress = "data/sound/brake.mp3";
	//�Ԃ��������̌��ʉ�
	const std::string carClashSEAddress = "data/sound/carClash.mp3";
	//�N���N�V�����̌��ʉ�
	const std::string carHornSEAddress = "data/sound/carHorn.mp3";
	//�^�]���̌��ʉ�
	const std::string drivingSEAddress = "data/sound/driving1.mp3";
	//�`�F�b�N�|�C���g�ɓ������Ă邩
	bool isGoalConflict;
	//�n�ʂɍ~��Ă��邩
	bool isOnGround;
	bool isDamage;

	//�^�C��
	Wheels* wheels;
	VECTOR itemEffecacyValue = {};
	//�ړI�n
	VECTOR destinationPos;
	//���̊p�x
	VECTOR destinationDir;
	//�Ԃ��������̂Ƃ̕���
	VECTOR conflictVec;
	//�^�C���ɓn���������
	WheelArgumentCarInfo wheelArgumentCarInfo;
};

