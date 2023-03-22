#pragma once
#include "DxLib.h"
#include "InputDirection.h"
#include "CheckPoint.h"
#include "AutoDriveInfo.h"
/// <summary>
/// ��G�c�Ȑi�s���������߂Ă����
/// </summary>
class DirectionOfTravelGenerator
{
public:
    DirectionOfTravelGenerator();
    ~DirectionOfTravelGenerator();

    static InputInfo GetPlayerDirection(AutoDriveInfo autoDriveParam);
    static InputInfo GetNextPointDirection(AutoDriveInfo autoDriveParam,VECTOR checkPointPos);
private :
    static InputInfo GetDirection(AutoDriveInfo autoDriveParam,VECTOR pos);
};