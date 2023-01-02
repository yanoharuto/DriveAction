#include "Car.h"
#include "Wheels.h"
#include "Utility.h"
Car::Car()
{
	tag = ObjectTag::car;
	radius = radiusValue;
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle, position);
	// �����ɍ��킹�ĉ�].
	MV1SetRotationZYAxis(modelHandle, direction, VGet(0.0f, 1.0f, 0.0f), 0.0f);
	// ���f���Ɍ����Ăق��������ɉ�].
	MATRIX tmpMat = MV1GetMatrix(modelHandle);
	MATRIX rotYMat = MGetRotY(180.0f * rage);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
	destinationPos = {};
	wheels = new Wheels(ArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
}

Car::~Car()
{
	MV1DeleteModel(modelHandle);
	SAFE_DELETE(wheels);
}

void Car::ConflictProcess(const ArgumentConflictInfo conflictInfo)
{
	switch (conflictInfo.tag)
	{
	case ObjectTag::car:
	case ObjectTag::stage:
	case ObjectTag::obstacle:
		ConflictReaction(conflictInfo.pos, conflictInfo.radius);
		break;
	case ObjectTag::goal:
		destinationPos = conflictInfo.pos;
#ifdef _DEBUG
		printfDx("%f,%f\n", conflictInfo.pos.x, conflictInfo.pos.z);
		printfDx("%f,%f\n", destinationPos.x, destinationPos.z);
#endif
		break;
	default:
		break;
	}
}

void Car::Draw()
{
	MV1DrawModel(modelHandle);
	wheels->Draw();
#ifdef _DEBUG
	DrawSphere3D(position,radius,5,GetColor(100,100,255), GetColor(100, 100, 255),false);
#endif
}

void Car::ConflictReaction(const VECTOR conflictObjPos, const float conflictObjRad)
{
	VECTOR nVSub = VSub(position,conflictObjPos);
	nVSub = VNorm(nVSub);
	accelPower -= accelPower * colideDecel;
	nVSub = VScale(nVSub,colideDecel);
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
void Car::UpdateVelocity(const float deltaTime, const VECTOR accelVec)
{
	//�^�C���̌�������i�s���������
	float theta = wheels->GetMoveDirTheta(VSize(velocity));
	theta *= gripPower;
	velocity = VTransform(velocity, MGetRotY(theta));
	// �x���V�e�B�����v�Z.
	velocity = VScale(VAdd(velocity, accelVec), deltaTime);
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
