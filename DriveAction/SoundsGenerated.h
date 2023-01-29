#pragma once
#include <string>
#include <list>
#include <map>
#include "DxLib.h"
/// <summary>
/// 発生した音についての構造体
/// </summary>
struct SoundsGenerated
{
    bool isGenerated;
    std::map<std::string,int> soundAddress;//音の素材の場所
    std::list<std::string> stopSoundAddress;//止める音
    VECTOR soundPosition;//音が発生した場所
};