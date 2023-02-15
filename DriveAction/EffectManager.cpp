#include <unordered_map>
#include "EffectManager.h"
#include "EffekseerForDXLib.h"

static std::unordered_map <std::string, int> effectMap;
EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
    for (auto ite = effectMap.begin(); ite != effectMap.end(); ite++)
    {
        DeleteEffekseerEffect((*ite).second);
    }
    effectMap.clear();
}

void EffectManager::LoadEffectManager(std::string address,float size)
{
    if (!effectMap.contains(address))
    {
        effectMap.insert(std::make_pair(address, LoadEffekseerEffect(address.c_str(), size)));
    }
}

int EffectManager::GetPlayEffect3D(std::string address)
{
    return PlayEffekseer3DEffect(effectMap[address.c_str()]);
}

int EffectManager::GetPlayEffect2D(std::string address)
{
    return PlayEffekseer3DEffect(effectMap[address.c_str()]);
}
