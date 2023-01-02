#include "Player.h"
#include "Wheels.h"
#include "Utility.h"	
#include <math.h>

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <returns></returns>
Player::Player()
{
	modelHandle = MV1LoadModel("data/model/Player/WhiteCar.mv1");
	position = firstPos;
	direction = firstDir;
	tag = ObjectTag::car;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <returns></returns>
Player::~Player()
{
	MV1DeleteModel(modelHandle);
	SAFE_DELETE(wheels);
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update(const float deltaTime, const bool outsideHitFlag)
{
	int inputKey = GetJoypadInputState(DX_INPUT_KEY);

	UpdateVelocity(deltaTime, GetAccelVec(inputKey, outsideHitFlag));
	UpdateMV1Pos();
	ModelSetMatrix();
	ArgumentCarInfo info = { MV1GetMatrix(modelHandle),direction,VSize(velocity) };
	//�E�����������Ă���
	if (inputKey & PAD_INPUT_RIGHT)
	{
		info.handleDir = HandleDirection::right;
	}
	else if (inputKey & PAD_INPUT_LEFT)
	{
		info.handleDir = HandleDirection::left;
	}
	else
	{
		info.handleDir = HandleDirection::straight;
	}
	// �^�C���̏���
	wheels->WheelUpdate(info);
}
/// <summary>
/// ���͏�񂩂�i�ތ����Ƒ���������
/// </summary>
/// <param name="inputKey">���͏��</param>
/// <param name="outsideHitFlag">�R�[�X�̊O���ɂԂ��������ǂ���</param>
/// <returns>���̍X�V�܂łɐi�ތ����Ƒ���</returns>
VECTOR Player::GetAccelVec(const int inputKey,const bool outsideHitFlag)
{
	// ��������.
	VECTOR accelVec = VGet(0, 0, 0);
	// ��������Ă��������.
	if (inputKey & PAD_INPUT_UP)
	{
		accelPower += accelPower > maxSpeed ? 0 : accelSpeed;
	}
	// ���������Ă����猸��.
	else if (inputKey & PAD_INPUT_DOWN)
	{
		accelPower -= accelPower * breakDecel;
	}
	// �~�܂��Ă���ꍇ�͌������Ȃ�.
	if (VSize(velocity) > 0)
	{
		// �E�����������Ă�����O���b�v�ɂ�錸��.
		if (inputKey & PAD_INPUT_RIGHT || inputKey & PAD_INPUT_LEFT)
		{
			accelPower -= accelPower * gripDecel;
		}
		// ���������Ȃ���Ό���.
		if (inputKey == 0)
		{
			accelPower -= accelPower * defaultDecel;
		}
		//�R�[�X�O�ɏo���猸��
		if (outsideHitFlag)
		{
			accelPower -= accelPower * outsideHitDecel;
		}
	}
	accelVec = VScale(direction, accelPower);
	return accelVec;
}
