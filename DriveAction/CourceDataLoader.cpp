#include "CourceDataLoader.h"
#include "Utility.h"
#include "StageSelect.h"
#include <iostream>
#include <fstream>
#include <string>

CourceDataLoader::CourceDataLoader()
{
    firstPosLoader = new VECTOR3Loader(prevAddress + StageSelect::GetLoadeStageName() + firstPosAddress);
    checkPointDirLoader = new VECTOR3Loader(prevAddress + StageSelect::GetLoadeStageName() + checkPointDirAddress);
    checkPointPosLoader = new VECTOR3Loader(prevAddress + StageSelect::GetLoadeStageName() + checkPointPosAddress);
}

CourceDataLoader::~CourceDataLoader()
{
    SAFE_DELETE(firstPosLoader);
    SAFE_DELETE(checkPointDirLoader);
    SAFE_DELETE(checkPointPosLoader);
}

const std::string CourceDataLoader::GetMiniMapImgAddress()
{
    std::string chara = prevAddress + StageSelect::GetLoadeStageName() + miniMapAddress;
    return chara;
}

const std::string CourceDataLoader::GetOutsideAddress()
{
    std::string chara = prevAddress + StageSelect::GetLoadeStageName() + outsideAddress;
    return chara;
}

const std::string CourceDataLoader::GetCourceAddress()
{
    std::string chara = prevAddress + StageSelect::GetLoadeStageName() + courceAddress;
    return chara;
}

const std::list<VECTOR> CourceDataLoader::GetFirstPosList()
{
    std::list<VECTOR> firstPosList = firstPosLoader->GetVectorList();
    firstPosList.erase(firstPosList.begin());
    return firstPosList;
}

const VECTOR CourceDataLoader::GetFirstDir()
{
    return *firstPosLoader->GetVectorList().begin();
}

const std::list<VECTOR> CourceDataLoader::GetCheckPointPosList()
{
    return checkPointPosLoader->GetVectorList();
}

const std::list<VECTOR> CourceDataLoader::GetCheckPointDirList()
{
    return checkPointDirLoader->GetVectorList();
}
