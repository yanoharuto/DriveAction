#pragma once
#include "DxLib.h"
//�n���h�����ǂ��������Ȃ̂�
enum class HandleDirection
{	
	straight,
	left,
	right,
};
/// <summary>
/// �^�C�����������Ă�����
/// </summary>
struct Wheel
{
	int modelHandle = -1;//Duplicate����̂Ŗ{�͕̂�
	VECTOR betweenBody = {};//�Ԃ܂ł̋���
	MATRIX matrix;
};
/// <summary>
/// �^�C���Ɉ����œn���Ăق����Ԃ̏��
/// </summary>
struct WheelArgumentCarInfo
{
	MATRIX matrix;//�Ԃ�model�̍s��
	VECTOR direction;//�Ԃ̌���
	float velocitySize;//�����̑傫��
	HandleDirection handleDir;	//�n���h�����ǂ��������Ȃ̂�
};

/// <summary>
/// �Ԃ����������n����B���ƃ^�C������]������`�悷��
/// </summary>
class Wheels 
{
public:
    Wheels(const WheelArgumentCarInfo InitInfo);
    ~Wheels();
    /// <summary>
    /// �`��
    /// </summary>
    void Draw();

	/// <summary>
	/// ���E�L�[����͂�����X���A�㉺�L�[�ŉ�]������
	/// </summary>
	/// <param name="_Key">���͏��</param>
	void WheelUpdate(const WheelArgumentCarInfo info);

	/// <summary>
	/// �ǂ̌����ɋȂ���΂������^���W�F���g��Ԃ���
	/// </summary>
	/// <param name="velocitySize">�����̃x�N�g���̑傫��</param>
	/// <returns>���̐��Ȃ炾�����獶</returns>
	float GetMoveDirTheta(const float velocitySize);
private:	
	/// <summary>
	/// ���̃G�t�F�N�g���o��
	/// </summary>
	/// <param name="pos"></param>
	void StartSmokeEffect(VECTOR pos);
	/// <summary>
	/// �S�Ẵ^�C���̃}�g���b�N�X���Z�b�g����
	/// </summary>
	void AllSetWheelMatrix();
	/// <summary>
/// ��]���邽�߂̔��a��Ԃ�
/// </summary>
/// <param name="firstWheelRota"></param>
/// <returns></returns>
	float GetRotationRadius(const float firstWheelRota);
	/// <summary>
    /// �Ԃ��猩���^�C���̍��W���Ԃ��Ă���
    /// </summary>
    /// <param name="_wheel"></param>
	VECTOR WheelGetPos(const Wheel& wheel);
	/// <summary>
    /// �^�C���̈ʒu�Ɖ�]��ݒ�
    /// </summary>
    /// <param name="_wheel">�ݒ肵�����^�C��</param>
    /// <param name="_rotaX">�^�C���̓]����Ƃ��̉�]</param>
    /// <param name="_rotaY">�^�C���̌����������Ƃ��̉�]</param>
	void SetWheelMatrix(Wheel& wheel, const float rotaX, const float rotaY);
	/// <summary>
	/// �^�C���̏�����
	/// </summary>
	/// <param name="_Wheel">�������������^�C��</param>
	/// <param name="_ModelHandle">�^�C���̃��f��</param>
	/// <param name="_Pos">�Ԃ��猩���ʒu</param>
	/// <param name="_Rota">��]�p</param>
	void InitWheel(Wheel& wheel, int DuplicateSourceModel, VECTOR pos, float rota);

	
	const float firstLWheelRota = 0.0f;		//�����^�C���̏����p�x
	const float firstRWheelRota = 180.0f;		//�E���^�C���̏����p�x
	const float wheelDriveRotaPower = 200.0f;//�Ԃ̉�]��
	const float wheelCurvePower = 1.7f;//�^�C�������E�ɌX����
	const float maxWheelRotaY = 45.5f;//���̊p�x�܂Ń^�C���͌X����
	const float rotaCalculationLine = 1.2f;//�i�s�����ɉe������܂łɕK�v�ȃ^�C���̊p�x
	const float rage = static_cast<float>(DX_PI / 180.0f);
	float wheelDriveSpeed = 0.0f;//�Ԃ̉�]���x
	float wheelDriveRota = 0.0f;//�Ԃ̍��E�ւ̌X��
	int effectResourceHandle = -1;//���̃G�t�F�N�g
	bool isStraightDash;//�܂������i��ł��邩�ǂ���
	int modelHandle;//�^�C���̃��f���n���h��
	Wheel lFWheel;
	Wheel lBWheel;
	Wheel rFWheel;
	Wheel rBWheel;
	WheelArgumentCarInfo carInfo;
	VECTOR wheelEffectPos;
	const VECTOR fWheelPos = { 2.7f,-0.8f,1.6f };
	const VECTOR bWheelPos = { 2.4f,-0.8f,1.6f };
};