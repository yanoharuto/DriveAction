#pragma once
#include <string>
#include <list>
#include <map>
#include "DxLib.h"
/// <summary>
/// ”­¶‚µ‚½‰¹‚É‚Â‚¢‚Ä‚Ì\‘¢‘Ì
/// </summary>
struct SoundsGenerated
{
    bool isGenerated;
    std::map<std::string,int> soundAddress;//‰¹‚Ì‘fŞ‚ÌêŠ
    std::list<std::string> stopSoundAddress;//~‚ß‚é‰¹
    VECTOR soundPosition;//‰¹‚ª”­¶‚µ‚½êŠ
};