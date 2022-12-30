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
	wheels->WheelUpdate(info);
#ifdef _DEBUG
	printfDx("%f,%f\n", position.x, position.z);
	printfDx("%f,%f\n", direction.x, direction.z);
#endif
}
/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	MV1DrawModel(modelHandle);
	wheels->Draw();
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
		accel += accel > maxSpeed ? 0 : accelSpeed;

		accelVec = VScale(direction, accel);
	}
	// ���������Ă����猸��.
	else if (inputKey & PAD_INPUT_DOWN)
	{
		accel += accel * breakDecel;
		accelVec = VScale(direction, accel);
	}
	// �~�܂��Ă���ꍇ�͌������Ȃ�.
	if (VSize(velocity) > 0)
	{
		// �E�����������Ă�����O���b�v�ɂ�錸��.
		if (inputKey & PAD_INPUT_RIGHT || inputKey & PAD_INPUT_LEFT)
		{
			accel += accel * gripDecel;
			accelVec = VScale(direction, accel);
		}
		// ���������Ȃ���Ό���.
		if (inputKey == 0)
		{
			accel += accel * defaultDecel;
			accelVec = VScale(direction, accel);
		}
		//�R�[�X�O�ɏo���猸��
		if (outsideHitFlag)
		{
			accel += accel * outsideHitDecel;
			accelVec = VScale(direction, accel);
		}
	}
	return accelVec;
}
