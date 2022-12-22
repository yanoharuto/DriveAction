#include "Player.h"
#include <math.h>
// �ÓI�萔.
const float Player::ACCEL = 3.0f;			 // �ʏ�̉���.
const float Player::MAX_SPEED = 180.0f;		 // �ō����x.	
const float Player::DEFAULT_DECEL = -0.004f;	 // �Ȃɂ����Ȃ����̌���.	
const float Player::BREAK_DECEL = -0.075f;	 // �u���[�L���̌���.	
const float Player::GRIP_DECEL = -0.025f;	 // �O���b�v�̌���.	
const float Player::GRIP_POWER = 1.2f;		 // �O���b�v��.	
const float Player::MAX_GRIP_POWER = 0.4f;		 // �O���b�v��.	
const float Player::COLIDE_DECEL_FAC = 0.4f; // ��Q���ɂԂ������Ƃ��̌�����.	
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <returns></returns>
Player::Player()
{
    modelHandle = MV1LoadModel("data/model/Player/RedCar.mv1");
	wheeleModelHandle = MV1LoadModel("data/model/Player/Wheel.mv1");
	position = firstPos;
	direction = firstRota;
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, position);
	// �����ɍ��킹�ĉ�].
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	// ���f���Ɍ����Ăق��������ɉ�].
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
	InitWheele(lFWheel, wheeleModelHandle, VGet(-fWheelPos.x,fWheelPos.y,-fWheelPos.z),firstLWheeleRota);
	InitWheele(lBWheel, wheeleModelHandle, VGet(bWheelPos.x, fWheelPos.y,-fWheelPos.z),firstLWheeleRota);
	InitWheele(rBWheel, wheeleModelHandle, VGet(bWheelPos.x, fWheelPos.y,fWheelPos.z),firstRWheeleRota);
	InitWheele(rFWheel, wheeleModelHandle, VGet(-fWheelPos.x, fWheelPos.y,fWheelPos.z),firstRWheeleRota);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <returns></returns>
Player::~Player()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(wheeleModelHandle);
	MV1DeleteModel(lFWheel.modelHandle);
	MV1DeleteModel(rFWheel.modelHandle);
	MV1DeleteModel(lBWheel.modelHandle);
	MV1DeleteModel(rBWheel.modelHandle);
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update(const float deltaTime)
{
	float theta = 0;
	// �E�������Ă�����E�����ɗ͂�������
	if (wheelDriveRota > rotaCalculationLine)
	{
		theta = GetCircleRadius(firstRWheeleRota);
		theta = atan2f(VSize(velocity), theta);
	}
	// ���������Ă����獶�����ɗ͂�������
	else if (wheelDriveRota < -rotaCalculationLine)
	{
		theta = GetCircleRadius(firstLWheeleRota);
		theta = atan2f(VSize(velocity), theta);
		theta = -theta;
	}
	theta *= GRIP_POWER;
	velocity = VTransform(velocity,MGetRotY(theta));

	// �L�[���͎擾
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ��������.
	VECTOR accelVec = VGet(0, 0, 0);
	// ��������Ă��������.
	if (Key & PAD_INPUT_UP)
	{
		accel += accel > MAX_SPEED ? 0 : ACCEL;

		accelVec = VScale(direction, accel);
	}
	// ���������Ă����猸��.
	else if (Key & PAD_INPUT_DOWN)
	{
		accel += accel * BREAK_DECEL;
		accelVec = VScale(direction, accel);
	}
	// �~�܂��Ă���ꍇ�͌������Ȃ�.
	if (VSize(velocity) > 0)
	{
		// �E�����������Ă�����O���b�v�ɂ�錸��.
		if (Key & PAD_INPUT_RIGHT || Key & PAD_INPUT_LEFT)
		{
			accel += accel * GRIP_DECEL;
			accelVec = VScale(direction, accel);
		}
		// ���������Ȃ���Ό���.
		if (Key == 0)
		{
			accel += accel * DEFAULT_DECEL;
			accelVec = VScale(direction, accel);
		}
	}

	// �x���V�e�B�����v�Z.
	velocity = VScale(VAdd(velocity, accelVec),deltaTime);

	// �㉺�����ɂ����Ȃ��悤�Ƀx���V�e�B�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);
	// ���Ε����ɐi�ޏ�ԂɂȂ��Ă�����~�߂�.
	if (VDot(velocity, direction) < 0)
	{
		velocity = VGet(0, 0, 0);
	}
	// �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
	if (VSize(velocity) != 0)
	{
		direction = VNorm(velocity);
	}
	// �|�W�V�������X�V.
	position = VAdd(position, velocity);
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, position);

	// �����ɍ��킹�ĉ�].
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	// ���f���Ɍ����Ăق��������ɉ�].
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);

	WheelUpdate(Key);

#ifdef _DEBUG
	//printfDx("%f,%f,%f:\n", tmpMat.m[0][0], tmpMat.m[0][1], tmpMat.m[0][2]) ;
	//printfDx("%f,%f,%f:\n", tmpMat.m[1][0], tmpMat.m[1][1], tmpMat.m[1][2]) ;
	//printfDx("%f,%f,%f:\n", tmpMat.m[2][0], tmpMat.m[2][1], tmpMat.m[2][2]) ;

	printfDx("%f,%f,%f:\n", position.x, position.y, position.z);
	printfDx("%f,%f,%f:\n", direction.x, direction.y, direction.z);
	
#endif // _DEBUG
}
/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	MV1DrawModel(modelHandle);
	MV1DrawModel(lBWheel.modelHandle);
	MV1DrawModel(lFWheel.modelHandle);
	MV1DrawModel(rFWheel.modelHandle);
	MV1DrawModel(rBWheel.modelHandle);
}
/// <summary>
/// �^�C���̏�����
/// </summary>
/// <param name="_Wheele">�������������^�C��</param>
/// <param name="_ModelHandle">�R�s�[���������f��</param>
/// <param name="_Pos">�^�C���̈ʒu</param>
/// <param name="_Rota">�^�C���̏����p�x</param>
void Player::InitWheele(Wheel& wheel, int modelHandle, VECTOR pos, float rota)
{
	wheel.modelHandle = MV1DuplicateModel(modelHandle);
	wheel.betweenBody = pos;
	VECTOR wheelPos = WheelGetPos(wheel);
	MATRIX bodyMat = MV1GetMatrix(modelHandle);
	wheel.matrix = MMult(MGetRotY(rota*DX_PI/180.0f), MMult(bodyMat,MGetTranslate(wheelPos)));
	MV1SetMatrix(wheel.modelHandle, wheel.matrix);
}
/// <summary>
/// ���E�L�[����͂�����X���A�㉺�L�[�ŉ�]������
/// </summary>
/// <param name="_Key">���͏��</param>
void Player::WheelUpdate(const int key)
{
	MATRIX bodyMat = MV1GetMatrix(modelHandle);
	MATRIX wheelRota;//�^�C���̉�]
	MATRIX wheelPos;//�^�C���̃|�W�V����
	//���O�^�C��
	SetWheelMatrix(lFWheel, wheelDriveSpeed, firstLWheeleRota + wheelDriveRota);
	//�����^�C��
	SetWheelMatrix(lBWheel, wheelDriveSpeed, firstLWheeleRota);
	//�E�O�^�C��	
	SetWheelMatrix(rFWheel, -wheelDriveSpeed, firstRWheeleRota + wheelDriveRota);
	//�E���^�C��
	SetWheelMatrix(rBWheel, -wheelDriveSpeed, firstRWheeleRota);
	if (VSize(velocity) > 0)
	{
		wheelDriveSpeed = -VSize(velocity) * wheeleDriveRotaSpeed;
	}
	else
	{
		wheelDriveSpeed = 0;
	}
	//�^�C�����X���鏈��
	if (key & PAD_INPUT_RIGHT)
	{
		if (wheelDriveRota < maxWheelRota)
		{
			wheelDriveRota += wheelCurvePower;
		}
		else
		{
			wheelDriveRota = maxWheelRota;
		}
	}
	else if (key & PAD_INPUT_LEFT)
	{
		if (wheelDriveRota > -maxWheelRota)
		{
			wheelDriveRota -= wheelCurvePower;
		}
		else
		{
			wheelDriveRota = -maxWheelRota;
		}
	}
	//�ǂ�����������ĂȂ�������^�C�������ɖ߂�
	else if (fabsf(wheelDriveRota) != rotaCalculationLine)
	{
		wheelDriveRota += wheelDriveRota > 0 ? -wheelCurvePower : wheelCurvePower;
	}
}
/// <summary>
/// �^�C���̈ʒu���A���Ă���
/// </summary>
/// <param name="_wheel">�ʒu��������Ȃ��^�C��</param>
/// <returns>�^�C���̈ʒu</returns>
VECTOR Player::WheelGetPos(const Wheel& wheel)
{
	//�^�C���̑O�������̈ʒu
	VECTOR between = VScale(direction, -wheel.betweenBody.x);
	//�^�C���̉������̈ʒu�Ƒ���
	between =VAdd(between,VScale(VCross(direction, VGet(0, 1, 0)), -wheel.betweenBody.z));
	//���������킹��
	between.y = fWheelPos.y;
	return  between;
}
/// <summary>
/// �^�C���̈ʒu�Ɖ�]��ݒ�
/// </summary>
/// <param name="_wheel">�ݒ肵�����^�C��</param>
/// <param name="_rotaX">�^�C���̓]����Ƃ��̉�]</param>
/// <param name="_rotaY">�^�C���̌����������Ƃ��̉�]</param>
void Player::SetWheelMatrix(Wheel& wheel,float rotaX,float rotaY)
{
	//�^�C���̈ʒu���Ԃ̌����ɍ��킹��
	MATRIX wheelPos = MMult(MV1GetMatrix(modelHandle), MGetTranslate(WheelGetPos(wheel)));
	
	MATRIX wheelRota = MMult(MGetRotX(rotaX * DX_PI / 180.0f), MGetRotY(rotaY * DX_PI / 180.0f));
	wheel.matrix = MMult(wheelRota,wheelPos);
	MV1SetMatrix(wheel.modelHandle,wheel.matrix);
}

float Player::GetCircleRadius(float firstWheelRota)
{
	if (fabsf(wheelDriveRota) > rotaCalculationLine)
	{
		float rota = tan(fabsf(wheelDriveRota) * DX_PI / 180);
		//��]���a���o��
		float radius = (fWheelPos.x + bWheelPos.x) / rota;
		//�Ԃ̌����Ɍ��^�C����Y������]������
		VECTOR bWDir = VTransform(direction, MGetRotY((firstWheelRota) * DX_PI / 180));
		//���^�C���̉��������o��
		bWDir = VNorm(VCross(bWDir, VGet(0, 1, 0)));
		//��]���a�̒��S���W���o��
		VECTOR circleAxisPos = VScale(bWDir, radius);

		//�i�s�����ɕK�v�ȉ�]���o��
		return  VSize(circleAxisPos);
	}
	return 0.0f;
}