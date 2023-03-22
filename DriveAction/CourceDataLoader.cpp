#include "CourceDataLoader.h"
#include "Utility.h"
#include "StageSelect.h"
#include <iostream>
#include <fstream>
#include <string>
//共通のアドレス
std::string CourceDataLoader::genericAddress;

/// <summary>
/// コース情報
/// </summary>
CourceDataLoader::CourceDataLoader()
{
    genericAddress = prevAddress + StageSelect::GetLoadeStageName();
}
CourceDataLoader::~CourceDataLoader()
{
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetStageDataGenericAddress()
{
    return genericAddress;
}

std::list<VECTOR> CourceDataLoader::GetVECTORData(std::string address)
{
    VECTOR3Loader* loader = new VECTOR3Loader(genericAddress + address);
    std::list<VECTOR> list = loader->GetVectorList();
    SAFE_DELETE(loader);
    return list;
}
