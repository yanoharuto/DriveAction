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

	//目的地までの距離
	VECTOR tempVec = VSub(VGet(pos.x, 0, pos.z), VGet(autoDriveParam.position.x, 0, autoDriveParam.position.z));
	//目的地までの角度差
	float angular = OriginalMath::GetDegreeMisalignment(autoDriveParam.direction, tempVec);
	//角度の差によって曲がるか決める
	if (angular > autoDriveParam.turnProccessLine)
	{
		//車の向いてる方向と目的地までの方向の外積を出して
		//右に曲がるか左に曲がるか調べる
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
		//曲がらなくていいならまっすぐに
		inputInfo.handleDir = HandleDirection::straight;

	};
	return inputInfo;
}
