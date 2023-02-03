#pragma once
#include "CpuCarMode.h"
#include "DxLib.h"
#include "Actor.h"
#include "Wheels.h"
#include "CarNeighborhoodExamineInfo.h"
#include "NeighborhoodInfo.h"
#include "SoundsGenerated.h"
#include "InputDirection.h"
/// <summary>
/// �Ԃ̉����Ƃ������Ƃ������B�ǂ̌����ɉ������邩�Ƃ���wheels����Ƃ��Ă����
/// </summary>
class Car :public Actor
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
	virtual void Update(const float deltaTime, const bool outsideHitFlag,VECTOR pos,SoundPlayer* soundPlayer){};
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
	/// ���ӂ𒲂ׂĂ��炤���߂ɓn��
	/// </summary>
	/// <returns></returns>
	CarNeighborhoodExamineInfo GetNeighExamineInfo();
	/// <summary>
	/// ���̑��x�͍ő呬�x�̉����Ȃ̂������o����
	/// </summary>
	/// <returns></returns>
	float GetAccelPowerPercent();
protected:
	/// <summary>
	/// ���e�U��
	/// </summary>
	void BombAttack();
	/// <summary>
	/// ���
	/// </summary>
	/// <param name="deltaTime"></param>
	void Fly(float deltaTime);
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="deltaTime"></param>
	void Down(float deltaTime);
	/// <summary>
	/// �����ł鎞�̏���
	/// </summary>
	/// <param name="deltaTime"></param>
	void FlyUpdate(float deltaTime);

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
	void AutoDrive(const float deltaTime, const bool outsideHitFlag , VECTOR pos ,SoundPlayer* soundPlayer);
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
	/// ���ӏ�񂩂�Ȃ�����ɉe����^����
	/// </summary>
	/// <param name="neighInfo"></param>
	/// <returns></returns>
	float GetNeighSize(NeighborhoodInfo neighInfo);
	/// <summary>
	/// �^�C���ɓn�����̏�����
	/// </summary>
	void InitWheelArgumentCarInfo();
	//�`�F�b�N�|�C���g�ɒʉ߂�����
	int checkCount = 0;
	// �ʏ�̉���.
	const float accelAddSpeed = 18.4f;					
	// �ʏ�ō����x.
	const float maxAccelSpeed = 200.0f;					
	//�O�I�v���̑����̍ō����x
	const float maxAddSpeed = 50.0f;
	//�O�I�v���̑���
	const float addAccelSpeed = 5.0f;
	//����ȉ��̑��x�ɂȂ��Ă���accelPower��0�ɂ����
	const float stopAccelLine = 0.03f;
	// �Ȃɂ����Ȃ����̌���.
	const float defaultDecel = 0.04f;			
	// �u���[�L���̌���.
	const float breakDecel = 0.97f;				
	// �O���b�v�̌���.
	const float gripDecel = 0.34f;				
	// �O���b�v��.
	const float gripPower = 0.036f;				
	// ��Q���ɂԂ������Ƃ��̌�����.
	const float colideDecel = 0.2f;	  
	//�R�[�X�̊O���ɗ������̌���
	const float outsideHitDecel = 0.4f;          
	//�Ԃ̕�
	const float radiusValue = 3.0f;              
	//�ړI�n�Ɍ������Ƃ��ɋȂ��邩���f����
	const float turnProccesAngularLine = 3.0f;  
	//���˕Ԃ�͂̌Œ�l
	const float setBouncePower = 1.0f;
	//���Ӓ����͈�
	const float examineRange = 150.0f;
	
	//����
	float accelPower = 0;                        
	//�O�I�v���ő����Ȃ�Ƒ�����
	float addForcePower = 0;
	//�Ԃ��������̒��˕Ԃ��
	float conflictObjBouncePower;
	//����Ԏ��p
	float flyY = 0;
	//���̃G�t�F�N�g
	int smokeEffectResource = -1;
	//�Ԃ��������̃G�t�F�N�g
	int conflictEffectResource = -1;
	//�O�I�v���ő����Ȃ������̃G�t�F�N�g
	int accelerationEffectResource = -1;
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

	float firstPosY = 0;
	float bombAttackTime = 0;
	const float bombCoolTime = 5;
	const float coolTime = 45.0f;
	const float flyPower = 0.6f;
	const float downSpeed = 0.37f;
	const float maxHeight = 1.0f;
	const float maxFlyTime = 15.0f;
	CarMode carMode = CarMode::normal;
	float flyTime = 0;

	//�^�C��
	Wheels* wheels;
	//�ړI�n
	VECTOR destinationPos;
	//���̊p�x
	VECTOR destinationDir;
	//�Ԃ��������̂Ƃ̕���
	VECTOR conflictVec;
	//�^�C���ɓn���������
	WheelArgumentCarInfo wheelArgumentCarInfo;
};

