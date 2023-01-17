#include "Car.h"
#include "Wheels.h"
#include "Utility.h"
#include "ArgumentObjInfoStruct.h"
#include <math.h>
Car::Car()
{
	tag = ObjectTag::car;
	radius = radiusValue;
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPos = {};
	wheels = new Wheels(ArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
}

Car::Car(VECTOR firstPos, VECTOR firstDir)
{
	position = firstPos;
	direction = firstDir;
	tag = ObjectTag::car;
	radius = radiusValue;
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPos = {};
	wheels = new Wheels(ArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
}

Car::~Car()
{
	MV1DeleteModel(modelHandle);
	SAFE_DELETE(wheels);
}

void Car::ConflictProcess(float deltaTime,const ArgumentConflictInfo conflictInfo)
{
	switch (conflictInfo.tag)
	{
	case ObjectTag::car:
	case ObjectTag::stage:
	case ObjectTag::obstacle:
		ConflictReaction(deltaTime,conflictInfo.pos, radius);
		break;
	case ObjectTag::goal:
		destinationPos = conflictInfo.pos;
		break;
	default:
		break;
	}
}

void Car::Draw()
{
	MV1DrawModel(modelHandle);
	wheels->Draw();
}

/// <summary>
/// �Ԃ��������̏����@��������
/// </summary>
/// <param name="conflictObjPos"></param>
/// <param name="conflictObjRad"></param>
void Car::ConflictReaction(float deltaTime, const VECTOR conflictObjPos, const float conflictObjRad)
{
	accelPower -= accelPower * colideDecel;
	VECTOR nVSub = VSub(position,conflictObjPos);
	nVSub = VNorm(nVSub);
	nVSub = VScale(nVSub,conflictObjRad);
	nVSub.y = 0;
	position = VAdd(position, nVSub);
}

void Car::DamageReaction(const VECTOR conflictObjPos, const float conflictObjRad)
{
}

/// <summary>
/// �i�ޕ����Ƒ������X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
/// <param name="accelVec">���̍X�V�܂łɐi�ޕ����Ƒ���</param>
void Car::UpdateVelocity(const VECTOR accelVec)
{
	velocity = accelVec;
	//�^�C���̌�������i�s���������
	float theta = wheels->GetMoveDirTheta(VSize(velocity));
	theta *= gripPower;
	velocity = VTransform(velocity, MGetRotY(theta));
	// �x���V�e�B�����v�Z.


	// �㉺�����ɂ����Ȃ��悤�Ƀx���V�e�B�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);	
}
/// <summary>
/// model�̕`��ꏊ���X�V
/// </summary>
void Car::UpdateMV1Pos()
{
	// �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
	if (VSize(velocity) != 0)
	{
		direction = VNorm(velocity);
	}
	// �|�W�V�������X�V.
	position = VAdd(position, velocity);
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, position);
}
/// <summary>
/// �Ԃ���]������
/// </summary>
void Car::ModelSetMatrix()
{
	// �����ɍ��킹�ĉ�].
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	// ���f���Ɍ����Ăق��������ɉ�].
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * rage);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}
/// <summary>
/// �������c�B
/// </summary>
/// <param name="deltaTime">�t���[���ԍ���</param>
/// <param name="outsideHitFlag">�R�[�X�O�ɏo����</param>
void Car::AutoDrive(const float deltaTime, const bool outsideHitFlag)
{
	ArgumentCarInfo info;
	info.handleDir = GetHandleDir();
	VECTOR accelVec = GetAccelVec(info.handleDir, outsideHitFlag, deltaTime);
	UpdateVelocity(VScale(accelVec, deltaTime));
	UpdateMV1Pos();
	ModelSetMatrix();
	info.matrix = MV1GetMatrix(modelHandle);
	info.velocitySize = VSize(velocity);
	info.direction = direction;

	wheels->WheelUpdate(info);
}

HandleDirection Car::GetHandleDir()
{
	float destinationDir = 0;//�ړI�n�Ƃ̋����̂���
	VECTOR distance = VSub(destinationPos, position);
	destinationDir = VDot(direction, distance) / (VSize(distance) * VSize(direction));
	destinationDir = acosf(destinationDir) / rage;

	if (destinationDir > turnProccesLine)
	{
		//�Ԃ̌����Ă�����ƖړI�n�܂ł̕����̊O�ς��o����
		//�E�ɋȂ��邩���ɋȂ��邩���ׂ�
		float crossY = VCross(VNorm(direction), VNorm(distance)).y;
		if (crossY > 0)
		{
			return HandleDirection::right;
		}
		else
		{
			return HandleDirection::left;
		}
	}
	
	return HandleDirection::straight;
}

/// <summary>
/// �������邽�߂̏���
/// </summary>
/// <param name="dir">�������Ă����</param>
/// <param name="outsideHitFlag"></param>
/// <returns></returns>
VECTOR Car::GetAccelVec(HandleDirection handleDir, bool outsideHitFlag, float deltaTime)
{
	// ��������.
	VECTOR accelVec = VGet(0, 0, 0);
	accelPower += accelPower > maxSpeed ? 0 : accelSpeed * deltaTime;

	// �~�܂��Ă���ꍇ�͌������Ȃ�.
	if (VSize(velocity) > 0)
	{
		//���E�ɋȂ��낤�Ƃ��Ă����猸��
		if (handleDir != HandleDirection::straight)
		{
			//���E�ɋȂ��낤�Ƃ����猸������
			accelPower -= accelPower * gripDecel * deltaTime;
		}
		//�R�[�X�O�ɏo���猸��
		if (outsideHitFlag)
		{
			accelPower -= accelPower * outsideHitDecel * deltaTime;
		}
	}
	accelVec = VScale(direction, accelPower);
	return accelVec;
}