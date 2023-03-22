#include "DirectionOfTravelGenerator.h"
#include "OriginalMath.h"
#include "PlayerInformationCenter.h"


DirectionOfTravelGenerator::DirectionOfTravelGenerator()
{
}

DirectionOfTravelGenerator::~DirectionOfTravelGenerator()
{
}

InputInfo DirectionOfTravelGenerator::GetPlayerDirection(AutoDriveInfo autoDriveParam)
{
	VECTOR playerPosition = PlayerInformationCenter::GetPlayerRelatedInfo(0).objInfo.pos;
	return GetDirection(autoDriveParam,playerPosition);
}

InputInfo DirectionOfTravelGenerator::GetNextPointDirection(AutoDriveInfo autoDriveParam, VECTOR checkPointPos)
{
	return GetDirection(autoDriveParam, checkPointPos);
}

InputInfo DirectionOfTravelGenerator::GetDirection(AutoDriveInfo autoDriveParam, VECTOR pos)
{
	InputInfo inputInfo = {};
	inputInfo.isBreake = false;

	//�ړI�n�܂ł̋���
	VECTOR tempVec = VSub(VGet(pos.x, 0, pos.z), VGet(autoDriveParam.position.x, 0, autoDriveParam.position.z));
	//�ړI�n�܂ł̊p�x��
	float angular = OriginalMath::GetDegreeMisalignment(autoDriveParam.direction, tempVec);
	//�p�x�̍��ɂ���ċȂ��邩���߂�
	if (angular > autoDriveParam.turnProccessLine)
	{
		//�Ԃ̌����Ă�����ƖړI�n�܂ł̕����̊O�ς��o����
		//�E�ɋȂ��邩���ɋȂ��邩���ׂ�
		float crossY = VCross(VNorm(autoDriveParam.direction), VNorm(tempVec)).y;
		if (crossY > 0)
		{
			inputInfo.handleDir = HandleDirection::right;
		}
		else
		{
			inputInfo.handleDir = HandleDirection::left;
		}
	}
	else
	{
		//�Ȃ���Ȃ��Ă����Ȃ�܂�������
		inputInfo.handleDir = HandleDirection::straight;

	};
	return inputInfo;
}
