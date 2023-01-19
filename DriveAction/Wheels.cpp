#include "Wheels.h"
#include "EffekseerForDXLib.h"
#include <math.h>
Wheels::Wheels(const WheelArgumentCarInfo InitInfo)
{
	modelHandle= MV1LoadModel("data/model/Player/Wheel.MV1");
	carInfo = InitInfo;
	InitWheel(lFWheel, modelHandle, VGet(-fWheelPos.x, fWheelPos.y, -fWheelPos.z), firstLWheelRota);
	InitWheel(lBWheel, modelHandle, VGet(bWheelPos.x, fWheelPos.y, -fWheelPos.z), firstLWheelRota);
	InitWheel(rBWheel, modelHandle, VGet(bWheelPos.x, fWheelPos.y, fWheelPos.z), firstRWheelRota);
	InitWheel(rFWheel, modelHandle, VGet(-fWheelPos.x, fWheelPos.y, fWheelPos.z), firstRWheelRota);
	effectResourceHandle = LoadEffekseerEffect("data/effect/smoke.efkefc", 0.4f);
}

Wheels::~Wheels()
{
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(lFWheel.modelHandle);
	MV1DeleteModel(rFWheel.modelHandle);
	MV1DeleteModel(lBWheel.modelHandle);
	MV1DeleteModel(rBWheel.modelHandle);
	// �G�t�F�N�g���\�[�X���폜����B(Effekseer�I�����ɔj�������̂ō폜���Ȃ��Ă�����)
	DeleteEffekseerEffect(effectResourceHandle);
}

void Wheels::Draw()
{
	MV1DrawModel(lBWheel.modelHandle);
	MV1DrawModel(lFWheel.modelHandle);
	MV1DrawModel(rFWheel.modelHandle);
	MV1DrawModel(rBWheel.modelHandle);
}

/// <summary>
/// ���E�L�[����͂�����X���A�㉺�L�[�ŉ�]������
/// </summary>
/// <param name="_Key">���͏��</param>
void Wheels::WheelUpdate(const WheelArgumentCarInfo info)
{
	carInfo = info;
	AllSetWheelMatrix();
	//�Ԃ������Ƃ悭���
	if (carInfo.velocitySize > 0)
	{
		wheelDriveSpeed = -carInfo.velocitySize * wheelDriveRotaPower;
	}
	else
	{
		wheelDriveSpeed = 0;
	}
	//�^�C�����X���鏈��
	if (carInfo.handleDir == HandleDirection::right)
	{
		wheelEffectPos.x = lBWheel.matrix.m[3][0];
		wheelEffectPos.y = lBWheel.matrix.m[3][1];
		wheelEffectPos.z = lBWheel.matrix.m[3][2];
		StartSmokeEffect(wheelEffectPos);
		
		isStraightDash = false;
		if (wheelDriveRota < maxWheelRotaY)
		{
			wheelDriveRota += wheelCurvePower;
		}
		else
		{
			wheelDriveRota = maxWheelRotaY;
		}

	}
	else if (carInfo.handleDir == HandleDirection::left)
	{

		wheelEffectPos.x = rBWheel.matrix.m[3][0];
		wheelEffectPos.y = rBWheel.matrix.m[3][1];
		wheelEffectPos.z = rBWheel.matrix.m[3][2];
		StartSmokeEffect(wheelEffectPos);
		
		isStraightDash = false;
		if (wheelDriveRota > -maxWheelRotaY)
		{
			wheelDriveRota -= wheelCurvePower;
		}
		else
		{
			wheelDriveRota = -maxWheelRotaY;
		}
	}
	//�ǂ�����������ĂȂ�������^�C�������ɖ߂�
	else if (fabsf(wheelDriveRota) > rotaCalculationLine)
	{
		wheelDriveRota += wheelDriveRota > 0 ? -wheelCurvePower : wheelCurvePower;
		//������x�߂��Ă���p�x��0�ɂ���
		if (fabsf(wheelDriveRota) < rotaCalculationLine)
		{
			wheelDriveRota = 0;
		}
		isStraightDash = true;
	}
	else
	{
		isStraightDash = true;
	}
	
	printfDx("wheelPos::%f,%f,%f\n", wheelEffectPos.x, wheelEffectPos.y, wheelEffectPos.z);
}

/// <summary>
/// �ǂ̌����ɋȂ���΂������^���W�F���g��Ԃ���
/// </summary>
/// <param name="velocitySize">�����̃x�N�g���̑傫��</param>
/// <returns>���̐��Ȃ炾�����獶</returns>
float Wheels::GetMoveDirTheta(const float velocitySize)
{
	if (wheelDriveRota > rotaCalculationLine)
	{
		return atan2f(velocitySize, GetRotationRadius(firstLWheelRota)); 
	}
	else if (wheelDriveRota < -rotaCalculationLine)
	{
		return -atan2f(velocitySize,GetRotationRadius(firstLWheelRota));
	}
	
	return 0.0f;
}
/// <summary>
/// ���̃G�t�F�N�g���o��
/// </summary>
/// <param name="pos"></param>
void Wheels::StartSmokeEffect(VECTOR pos)
{
	if (isStraightDash)
	{

		int playingEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);
		int effectSuccess = SetPosPlayingEffekseer3DEffect(playingEffectHandle, pos.x,pos.y,pos.z);
	}
}
void Wheels::AllSetWheelMatrix()
{
	//���O�^�C��
	SetWheelMatrix(lFWheel, wheelDriveSpeed, firstLWheelRota + wheelDriveRota);
	//�����^�C��
	SetWheelMatrix(lBWheel, wheelDriveSpeed, firstLWheelRota);
	//�E�O�^�C��	
	SetWheelMatrix(rFWheel, -wheelDriveSpeed, firstRWheelRota + wheelDriveRota);
	//�E���^�C��
	SetWheelMatrix(rBWheel, -wheelDriveSpeed, firstRWheelRota);
}
/// <summary>
/// ��]���邽�߂̔��a��Ԃ�
/// </summary>
/// <param name="firstWheelRota"></param>
/// <returns></returns>
float Wheels::GetRotationRadius(const float firstWheelRota)
{

	if (fabsf(wheelDriveRota) > rotaCalculationLine)
	{
		//�^�C���̊p�x���^���W�F���g��
		float rota = tan(static_cast<double> (fabsf(wheelDriveRota)) * rage);
		//��]���a���o��
		float radius = (fWheelPos.x + bWheelPos.x) / rota;
		//�Ԃ̌����Ɍ��^�C����Y������]������
		VECTOR bWDir = VTransform(carInfo.direction, MGetRotY((firstWheelRota) * rage));
		//���^�C���̉��������o��
		bWDir = VNorm(VCross(bWDir, VGet(0, 1, 0)));
		//��]���a�̒��S���W���o��
		VECTOR circleAxisPos = VScale(bWDir, radius);

		//�i�s�������Ȃ���̂ɕK�v�ȉ~�̔��a���o��
		return  VSize(circleAxisPos);
	}
	return 0.0f;
}
/// <summary>
	/// �Ԃ��猩���^�C���̍��W���Ԃ��Ă���
	/// </summary>
	/// <param name="_wheel"></param>
VECTOR Wheels::WheelGetPos(const Wheel& wheel)
{
	//�^�C���̑O�������̈ʒu
	VECTOR between = VScale(carInfo.direction, -wheel.betweenBody.x);
	//�^�C���̉������̈ʒu�Ƒ���
	between = VAdd(between, VScale(VCross(carInfo.direction, VGet(0, 1, 0)), -wheel.betweenBody.z));
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

void Wheels::SetWheelMatrix(Wheel& wheel, const float rotaX, const float rotaY)
{
	//�^�C���̈ʒu���Ԃ̌����ɍ��킹��
	MATRIX wheelPos = MMult(carInfo.matrix, MGetTranslate(WheelGetPos(wheel)));

	MATRIX wheelRota = MMult(MGetRotX(rotaX * rage), MGetRotY(rotaY * rage));
	wheel.matrix = MMult(wheelRota, wheelPos);
	MV1SetMatrix(wheel.modelHandle, wheel.matrix);
}
/// <summary>
/// �^�C���̏�����
/// </summary>
/// <param name="_Wheel">�������������^�C��</param>
/// <param name="_ModelHandle">�^�C���̃��f��</param>
/// <param name="_Pos">�Ԃ��猩���ʒu</param>
/// <param name="_Rota">��]�p</param>
void Wheels::InitWheel(Wheel& wheel, int DuplicateSourceModel, VECTOR pos, float rota)
{
	wheel.modelHandle = MV1DuplicateModel(DuplicateSourceModel);
	wheel.betweenBody = pos;
	VECTOR wheelPos = WheelGetPos(wheel);
	MATRIX bodyMat = MV1GetMatrix(DuplicateSourceModel);

	wheel.matrix = MMult(MGetRotY(rota * rage), MMult(bodyMat, MGetTranslate(wheelPos)));
	MV1SetMatrix(wheel.modelHandle, wheel.matrix);
}