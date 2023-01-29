#include "OriginalMath.h"
#include "Car.h"
#include "Wheels.h"
#include "Utility.h"
#include "ConflictExamineResultInfo.h"
#include "EffekseerForDXLib.h"

Car::Car()
{
	tag = ObjectTag::car;
	radius = radiusValue;
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPos = {};
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
	smokeEffectResource = LoadEffekseerEffect("data/effect/smoke.efkefc", 1.0f);
	conflictEffectResource = LoadEffekseerEffect("data/effect/conflict.efkefc", 1.0f);

}

Car::Car(VECTOR firstPos, VECTOR firstDir, VECTOR firstDestinationPos,SoundPlayer* soundPlayer)
{
	position = firstPos;
	direction = firstDir;
	tag = ObjectTag::car;
	bouncePower = setBouncePower;
	radius = radiusValue;
	UpdateMV1Pos();
	ModelSetMatrix();
	destinationPos = firstDestinationPos;
	wheels = new Wheels(WheelArgumentCarInfo{ MV1GetMatrix(modelHandle),direction,VSize(velocity) });
	smokeEffectResource = LoadEffekseerEffect("data/effect/smoke.efkefc", 1.0f);
	conflictEffectResource = LoadEffekseerEffect("data/effect/conflict.efkefc", 1.0f);
	accelerationEffectResource = LoadEffekseerEffect("data/effect/accelation.efkefc", 20.0f);

	soundPlayer->Add3DSound(drivingSEAddress);

	soundPlayer->Add3DSound(carClashSEAddress);

	soundPlayer->Add3DSound(carHornSEAddress);
	
	soundPlayer->Add3DSound(drivingSEAddress);
	
}

Car::~Car()
{
	MV1DeleteModel(modelHandle);
	DeleteEffekseerEffect(smokeEffectResource);
	DeleteEffekseerEffect(conflictEffectResource);
	DeleteEffekseerEffect(accelerationEffectResource);
	SAFE_DELETE(wheels);
}
/// <summary>
/// �Ԃ��������̏���
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="conflictInfo"></param>
void Car::ConflictProcess(float deltaTime,const ConflictExamineResultInfo conflictInfo, SoundPlayer* soundPlayer)
{
	switch (conflictInfo.tag)
	{
	case ObjectTag::car:
	case ObjectTag::stage:
	case ObjectTag::obstacle:
		ConflictReaction(deltaTime,conflictInfo,soundPlayer);
		break;
	case ObjectTag::goal:
		destinationPos = conflictInfo.pos;
		break;
	case ObjectTag::acelerationFloor: 

		accelPower += 5.0f;
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

CarNeighborhoodExamineInfo Car::GetNeighExamineInfo()
{
	CarNeighborhoodExamineInfo examineInfo;
	examineInfo.pos = position;
	examineInfo.range = examineRange;
	return examineInfo;
}

/// <summary>
/// �Ԃ��������̏����@��������
/// </summary>
/// <param name="conflictObjPos"></param>
/// <param name="conflictObjRad"></param>
void Car::ConflictReaction(float deltaTime, const ConflictExamineResultInfo conflictInfo, SoundPlayer* soundPlayer)
{
	soundPlayer->SetSoundVolume(MAX1BYTEVALUE, carClashSEAddress);
	soundPlayer->SetSoundRadius(MAX1BYTEVALUE, carClashSEAddress);
	soundPlayer->SetPosition3DSound(position, carClashSEAddress);
	soundPlayer->Play3DSE(position, carClashSEAddress);

	soundPlayer->SetSoundVolume(MAX1BYTEVALUE, carHornSEAddress);
	soundPlayer->SetSoundRadius(MAX1BYTEVALUE, carHornSEAddress);
	soundPlayer->SetPosition3DSound(position, carHornSEAddress);
	soundPlayer->Play3DSE(position, carHornSEAddress);
	//�Փ˃G�t�F�N�g
	int playingEffect = PlayEffekseer3DEffect(conflictEffectResource);
	SetPosPlayingEffekseer3DEffect(playingEffect, position.x, position.y, position.z);
	//�Փˏ���
	accelPower -= accelPower * colideDecel;
	conflictVec = VSub(position, conflictInfo.pos);
	conflictVec = VNorm(conflictVec);
	conflictVec.y = 0;
	position = VAdd(position, VScale(conflictVec,conflictInfo.radius));
	conflictObjBouncePower = conflictInfo.bouncePower;
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
	if (conflictObjBouncePower > 0.0f)
	{
		conflictObjBouncePower -= conflictObjBouncePower * defaultDecel;
		conflictObjBouncePower = conflictObjBouncePower > 0 ? conflictObjBouncePower : 0;
		position = VAdd(position, VScale(conflictVec,conflictObjBouncePower));
	}
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
	MATRIX rotYMat = MGetRotY(180.0f * RAGE);
	tmpMat = MMult(tmpMat, rotYMat);
	MV1SetRotationMatrix(modelHandle, tmpMat);
}
/// <summary>
/// �������c�B
/// </summary>
/// <param name="deltaTime">�t���[���ԍ���</param>
/// <param name="outsideHitFlag">�R�[�X�O�ɏo����</param>
void Car::AutoDrive(const float deltaTime, const bool outsideHitFlag,NeighborhoodInfo neighInfo, SoundPlayer* soundPlayer)
{
	wheelArgumentCarInfo.handleDir = GetHandleDir();
	VECTOR accelVec = GetAccelVec(wheelArgumentCarInfo.handleDir, outsideHitFlag, deltaTime,soundPlayer);
	UpdateVelocity(VScale(accelVec, deltaTime));
	UpdateMV1Pos();
	ModelSetMatrix();
	InitWheelArgumentCarInfo();
	wheels->WheelUpdate(wheelArgumentCarInfo);
}


/// <summary>
/// �n���h���̌������o��
/// </summary>
/// <returns></returns>
HandleDirection Car::GetHandleDir()
{
	//�ړI�n�܂ł̋���
	VECTOR destinationBetween = VSub(destinationPos, position);
	OriginalMath math;
	float angular = math.GetDegreeMisalignment(direction, destinationBetween);
	if (angular > turnProccesLine)
	{
		//�Ԃ̌����Ă�����ƖړI�n�܂ł̕����̊O�ς��o����
		//�E�ɋȂ��邩���ɋȂ��邩���ׂ�
		float crossY = VCross(VNorm(direction), VNorm(destinationBetween)).y;
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
VECTOR Car::GetAccelVec(HandleDirection handleDir, bool outsideHitFlag, float deltaTime, SoundPlayer* soundPlayer)
{
	if (handleDir == HandleDirection::brake)//�u���[�L
	{
		accelPower -= accelPower * breakDecel * deltaTime;

		soundPlayer->StopSound(drivingSEAddress);
		if (!soundPlayer->IsPlaySound(breakeSEAddress))
		{
			soundPlayer->SetSoundRadius(MAX1BYTEVALUE, breakeSEAddress);
			soundPlayer->SetSoundVolume(MAX1BYTEVALUE, breakeSEAddress);
			soundPlayer->SetPosition3DSound(position, breakeSEAddress);
			soundPlayer->Play3DSE(position, breakeSEAddress);
		}
	}
	else if (handleDir != HandleDirection::non)//�������͂��Ă��Ȃ��Ȃ�
	{
		// ��������.
		accelPower += accelPower > maxSpeed ? 0 : accelSpeed * deltaTime;

		soundPlayer->SetSoundRadius(MAX1BYTEVALUE, drivingSEAddress);
		soundPlayer->SetSoundVolume(MAX1BYTEVALUE, drivingSEAddress);
		soundPlayer->SetPosition3DSound(position, drivingSEAddress);
		if(!soundPlayer->IsPlaySound(drivingSEAddress))
		{

			soundPlayer->Play3DSE(position, drivingSEAddress);
		}
	}

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
	else//�~�܂����特���~�߂�
	{
		soundPlayer->StopSound(drivingSEAddress);
	}

	return VScale(direction, accelPower);
}

float Car::GetNeighSize(NeighborhoodInfo neighInfo)
{
	float angular = 0;
	float neighSize;
	if (neighInfo.outside.hitFlag)
	{
	}
	return angular;
}

void Car::InitWheelArgumentCarInfo()
{
	wheelArgumentCarInfo.matrix = MV1GetMatrix(modelHandle);
	wheelArgumentCarInfo.direction = direction;
	wheelArgumentCarInfo.velocitySize = VSize(velocity);
}

float Car::GetAccelPower()
{
	return accelPower;
}
