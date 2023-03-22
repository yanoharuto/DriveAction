#pragma once
#include "DxLib.h"
#include "InputDirection.h"
#include "CheckPoint.h"
#include "AutoDriveInfo.h"
/// <summary>
/// ‘åG”c‚Èis•ûŒü‚ğŒˆ‚ß‚Ä‚­‚ê‚é
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