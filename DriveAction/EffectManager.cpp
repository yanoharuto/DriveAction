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

void EffectManager::LoadEffectManager(std::string Pass,float size)
{
    if (!effectMap.contains(Pass))
    {
        std::string effectPass = "data/effect/" + Pass;
        effectMap.insert(std::make_pair(Pass, LoadEffekseerEffect(effectPass.c_str(), size)));
    }
}

int EffectManager::GetPlayEffect3D(std::string Pass)
{
    int handle = -1;
    if (effectMap.contains(Pass))
    {
        handle = PlayEffekseer3DEffect(effectMap[Pass.c_str()]);
    }
    return handle;
}

int EffectManager::GetPlayEffect2D(std::string Pass)
{
    return PlayEffekseer3DEffect(effectMap[Pass.c_str()]);
}

bool EffectManager::IsPlayEffect(std::string Pass)
{
    return IsEffekseer3DEffectPlaying(effectMap[Pass.c_str()]);
}