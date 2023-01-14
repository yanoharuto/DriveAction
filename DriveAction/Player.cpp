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
	Init();
}

Player::Player(VECTOR firstPos, VECTOR firstDir)
	:Car(firstPos,firstDir)
{
	Init();
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

	UpdateVelocity(VScale(GetAccelVec(inputKey, outsideHitFlag,deltaTime),deltaTime));
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
#ifdef _DEBUG
	//printfDx("%f,%f\n", position.x,position.z);
	//printfDx("%f,%f\n", direction.x,direction.z);
#endif
}
/// <summary>
/// ���͏�񂩂�i�ތ����Ƒ���������
/// </summary>
/// <param name="inputKey">���͏��</param>
/// <param name="outsideHitFlag">�R�[�X�̊O���ɂԂ��������ǂ���</param>
/// <returns>���̍X�V�܂łɐi�ތ����Ƒ���</returns>
VECTOR Player::GetAccelVec(const int inputKey,const bool outsideHitFlag, float deltaTime)
{
	// ��������.
	VECTOR accelVec = VGet(0, 0, 0);
	// ��������Ă��������.
	if (inputKey & PAD_INPUT_UP)
	{
		//���x���ō�����Ȃ����������
		accelPower += accelPower > maxSpeed ? 0 : accelSpeed * deltaTime;
	}
	// ���������Ă����猸��.
	else if (inputKey & PAD_INPUT_DOWN)
	{
		accelPower *= breakDecel * deltaTime;
	}
	// �~�܂��Ă���ꍇ�͌������Ȃ�.
	if (VSize(velocity) > 0)
	{
		// �E�����������Ă�����O���b�v�ɂ�錸��.
		if (inputKey & PAD_INPUT_RIGHT || inputKey & PAD_INPUT_LEFT)
		{
			accelPower *= gripDecel * deltaTime;
		}
		// ���������Ȃ���Ό���.
		if (inputKey == 0)
		{
			accelPower *= defaultDecel * deltaTime;
		}
		//�R�[�X�O�ɏo���猸��
		if (outsideHitFlag)
		{
			accelPower = outsideHitDecel * deltaTime;
		}
	}
	accelVec = VScale(direction, accelPower);
	return accelVec;
}

void Player::Init()
{
	modelHandle = MV1LoadModel("data/model/Player/WhiteCar.mv1");
}
