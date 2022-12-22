#pragma once
#include "Actor.h"
struct Wheel
{
	int modelHandle = -1;
	VECTOR betweenBody = {};
	VECTOR direction = {};
	MATRIX matrix = {};
};
enum WheelDirection
{
	left,
	right,
	normal
};
 /// <summary>
 /// �v���C���[(��)
 /// </summary>
 class Player final: public Actor
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <returns></returns>
	Player();
	///�f�X�g���N�^
    ~Player();
    /// <summary>
    /// �X�V�i�ړ������j
    /// </summary>
    void Update(const float deltaTime) override;
    /// <summary>
    /// �`��
    /// </summary>
    void Draw() override;
private:
	/// <summary>
	/// �^�C���̏�����
	/// </summary>
	/// <param name="_Wheele">�������������^�C��</param>
	/// <param name="_ModelHandle">�^�C���̃��f��</param>
	/// <param name="_Pos">�Ԃ��猩���ʒu</param>
	/// <param name="_Rota">��]�p</param>
	void InitWheele(Wheel& wheele,int modelHandle, VECTOR pos, float _rota);
	/// <summary>
	/// ���E�L�[����͂�����X���A�㉺�L�[�ŉ�]������
	/// </summary>
	/// <param name="_Key">���͏��</param>
	void WheelUpdate(const int key);
	/// <summary>
	/// �^�C���̈ʒu���Ԃɍ��킹��
	/// </summary>
	/// <param name="_wheel"></param>
	VECTOR WheelGetPos(const Wheel& wheel);
	/// <summary>
	/// �^�C���̈ʒu�Ɖ�]��ݒ�
	/// </summary>
	/// <param name="_wheel">�ݒ肵�����^�C��</param>
	/// <param name="_rotaX">�^�C���̓]����Ƃ��̉�]</param>
	/// <param name="_rotaY">�^�C���̌����������Ƃ��̉�]</param>
	void SetWheelMatrix(Wheel& wheel,const float rotaX,const float rotaY);

	float GetCircleRadius(float firstWheelRota);
	// �ÓI�萔.
	static const float ACCEL;					// �ʏ�̉���.
	static const float MAX_SPEED;				// �ō����x.
	static const float DEFAULT_DECEL;			// �Ȃɂ����Ȃ����̌���.
	static const float BREAK_DECEL;				// �u���[�L���̌���.
	static const float GRIP_DECEL;				// �O���b�v�̌���.
	static const float GRIP_POWER;				// �O���b�v��.
	static const float MAX_GRIP_POWER;				// �ő�O���b�v��.
	static const float COLIDE_DECEL_FAC;	    // ��Q���ɂԂ������Ƃ��̌�����.
	const float firstLWheeleRota = 0.0f;		//�����^�C���̏����p�x
	const float firstRWheeleRota = 180.0f;		//�E���^�C���̏����p�x
	const float wheeleDriveRotaSpeed = 200.0f;
	const float wheelCurvePower = 1.7f;
	const float maxWheelRota = 45.5f;
	const float rotaCalculationLine = 1.2f;
	WheelDirection wheelDir;
	float accel = 0;
	float wheelDriveSpeed = 0.0f;
	float wheelDriveRota = 0.0f;

	int wheeleModelHandle;
	Wheel lFWheel;
	Wheel lBWheel;
	Wheel rFWheel;
	Wheel rBWheel;
	const VECTOR fWheelPos = {2.7f,-0.8f,1.6f};
	const VECTOR bWheelPos = {2.4f,-0.8f,1.6f};
	const VECTOR firstPos = { -300.0f,-4.8f,-83.0f };
	const VECTOR firstRota = { -0.9f,0,-0.02f };
};

