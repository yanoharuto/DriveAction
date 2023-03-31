#include "CourceDataLoader.h"
#include "Utility.h"
#include "StageSelect.h"
#include <iostream>
#include <fstream>
#include <string>
//共通のアドレス
std::string CourceDataLoader::genericPass;

/// <summary>
/// コース情報
/// </summary>
CourceDataLoader::CourceDataLoader()
{
    genericPass = prevPass + StageSelect::GetLoadeStageName();
}
CourceDataLoader::~CourceDataLoader()
{
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
const std::string CourceDataLoader::GetStageDataGenericPass()
{
    return genericPass;
}

std::list<VECTOR> CourceDataLoader::GetVECTORData(std::string Pass)
{
    VECTOR3Loader* loader = new VECTOR3Loader(genericPass + Pass);
    std::list<VECTOR> list = loader->GetVectorList();
    SAFE_DELETE(loader);
    return list;
}
