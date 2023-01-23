#include "CourceDataLoader.h"
#include "Utility.h"
#include "StageSelect.h"
#include <iostream>
#include <fstream>
#include <string>
/// <summary>
/// コース情報
/// </summary>
CourceDataLoader::CourceDataLoader()
{
    genericAddress = prevAddress + StageSelect::GetLoadeStageName();
    //コース上のオブジェクトの位置とか向きとか
    firstCarPosLoader = new VECTOR3Loader(genericAddress + firstPosAddress);
    checkPointDirLoader = new VECTOR3Loader(genericAddress + checkPointDirAddress);
    checkPointPosLoader = new VECTOR3Loader(genericAddress + checkPointPosAddress);
    accelFloorDirLoader = new VECTOR3Loader(genericAddress + accelerationFloorDirAddress);
    accelFloorPosLoader = new VECTOR3Loader(genericAddress + accelerationFloorPosAddress);
    obstraclePosLoader = new VECTOR3Loader(genericAddress + obstaclePosListAddress);
}
CourceDataLoader::~CourceDataLoader()
{
    SAFE_DELETE(firstCarPosLoader);
    SAFE_DELETE(checkPointDirLoader);
    SAFE_DELETE(checkPointPosLoader);
    SAFE_DELETE(accelFloorPosLoader);
    SAFE_DELETE(accelFloorDirLoader);
    SAFE_DELETE(obstraclePosLoader);
}
/// <summary>
/// コースのミニマップ
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetMiniMapImgAddress()
{
    std::string chara = genericAddress + miniMapAddress;
    return chara;
}
/// <summary>
/// コースの外側のアドレス
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetOutsideAddress()
{
    std::string chara = genericAddress + outsideAddress;
    return chara;
}
/// <summary>
/// コースのmodelのアドレス
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetCourceAddress()
{
    std::string chara = genericAddress + courceAddress;
    return chara;
}
/// <summary>
/// 障害物のアドレス
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetObstracleAddress()
{
    std::string chara = prevAddress + obstacleModelAddress;
    return chara;
}
/// <summary>
/// 車の初期位置
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetCarFirstPosList()
{
    std::list<VECTOR> firstPosList = firstCarPosLoader->GetVectorList();
    return firstPosList;
}
/// <summary>
/// 車の初期方向
/// </summary>
/// <returns></returns>
const VECTOR CourceDataLoader::GetCarFirstDir()
{
    return *firstCarPosLoader->GetVectorList().begin();
}
/// <summary>
/// チェックポイントの位置リスト
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetCheckPointPosList()
{
    return checkPointPosLoader->GetVectorList();
}
/// <summary>
/// チェックポイントの方向リスト
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetCheckPointDirList()
{
    return checkPointDirLoader->GetVectorList();
}
/// <summary>
/// 加速床の位置リスト
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetAccelFloorPosList()
{
    return accelFloorPosLoader->GetVectorList();
}
/// <summary>
/// 加速床の向きリスト
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetAccelFloorDirList()
{
    return accelFloorDirLoader->GetVectorList();
}
/// <summary>
/// 障害物の位置リスト
/// </summary>
/// <returns></returns>
const std::list<VECTOR> CourceDataLoader::GetObstraclePosList()
{
    return obstraclePosLoader->GetVectorList();
}
