#include "CourceDataLoader.h"
#include "Utility.h"
#include "StageSelect.h"
#include <iostream>
#include <fstream>
#include <string>
//共通のアドレス
static std::string genericAddress;
//車の初期位置リストを読み取る
static VECTOR3Loader* firstCarPosLoader;
//チェックポイントの位置リストを読み取る
static VECTOR3Loader* checkPointPosLoader;
//チェックポイントの方向リストを読み取る
static VECTOR3Loader* checkPointDirLoader;
//加速床の位置リストを読み取る
static VECTOR3Loader* accelFloorPosLoader;
//加速床の向きリストを読み取る
static VECTOR3Loader* accelFloorDirLoader;
//障害物の位置リストを読み取る
static VECTOR3Loader* obstraclePosLoader;
static VECTOR3Loader* itemDirLoader;
static VECTOR3Loader* itemPosLoader;
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
    itemDirLoader = new VECTOR3Loader(genericAddress + itemBoxDirAddress);
    itemPosLoader = new VECTOR3Loader(genericAddress + itemBoxPosAddress);
}
CourceDataLoader::~CourceDataLoader()
{
    SAFE_DELETE(firstCarPosLoader);
    SAFE_DELETE(checkPointDirLoader);
    SAFE_DELETE(checkPointPosLoader);
    SAFE_DELETE(accelFloorPosLoader);
    SAFE_DELETE(accelFloorDirLoader);
    SAFE_DELETE(obstraclePosLoader);
    SAFE_DELETE(itemPosLoader);
    SAFE_DELETE(itemDirLoader);
}
/// <summary>
/// コースのミニマップ
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetStageDataGenericAddress()
{
    return genericAddress;
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

const std::list<VECTOR> CourceDataLoader::GetItemPosList()
{
    return itemPosLoader->GetVectorList();
}

const std::list<VECTOR> CourceDataLoader::GetItemDirList()
{
    return itemDirLoader->GetVectorList();
}
