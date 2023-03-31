#pragma once
#include <string>
class EffectManager
{
public:
    EffectManager();
    ~EffectManager();
    static void LoadEffectManager(std::string Pass,float size);
    static int GetPlayEffect3D(std::string Pass);
    static int GetPlayEffect2D(std::string Pass);
    static bool IsPlayEffect(std::string Pass);
};