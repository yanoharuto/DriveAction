#include "Player.h"
#include "Wheels.h"
#include "Utility.h"	
#include <math.h>
#include "EffekseerForDXLib.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <returns></returns>
Player::Player()
{
	Init();
}

Player::Player(VECTOR firstPos, VECTOR firstDir,VECTOR destinationPos)
	:Car(firstPos,firstDir,destinationPos)
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
void Player::Update(const float deltaTime, const bool outsideHitFlag, NeighborhoodInfo neighInfo)
{
	int inputKey = GetJoypadInputState(DX_INPUT_KEY);
	VECTOR accelVec = GetAccelVec(inputKey, outsideHitFlag, deltaTime);
	UpdateVelocity(VScale(accelVec,deltaTime));
	UpdateMV1Pos();
	ModelSetMatrix();
	WheelArgumentCarInfo info = { MV1GetMatrix(modelHandle),direction,VSize(velocity) };
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
	//printfDx("%f,%f\n", accelVec.x,accelVec.z);
	printfDx("%f,%f\n", position.x,position.z);
	printfDx("%f,%f\n", direction.x,direction.z);
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
	// ��������Ă��������.
	if (inputKey & PAD_INPUT_UP)
	{
		//���x���ō�����Ȃ����������
		accelPower += accelPower > maxSpeed ? 0 : accelSpeed * deltaTime;

	}
	// ���������Ă����猸��.
	else if (inputKey & PAD_INPUT_DOWN)
	{
		accelPower -= accelPower * breakDecel * deltaTime;
	}
	// �~�܂��Ă���ꍇ�͌������Ȃ�.
	if (VSize(velocity) > 0)
	{
		// �E�����������Ă�����O���b�v�ɂ�錸��.
		if (inputKey & PAD_INPUT_RIGHT || inputKey & PAD_INPUT_LEFT)
		{
			accelPower -= accelPower * gripDecel * deltaTime;
		}
		// ���������Ȃ���Ό���.
		else if (inputKey == 0)
		{
			accelPower -= accelPower * defaultDecel * deltaTime;
		}
		//�R�[�X�O�ɏo���猸��
		if (outsideHitFlag)
		{
			accelPower -= accelPower * outsideHitDecel * deltaTime;
		}
	}
	//printfDx("%f\n", accelPower);
	VECTOR accelVec = VScale(direction, accelPower);
	return accelVec;
}

void Player::Init()
{
	modelHandle = MV1LoadModel("data/model/Player/WhiteCar.mv1");
}
