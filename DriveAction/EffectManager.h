#pragma once
#include <string>
class EffectManager
{
public:
    EffectManager();
    ~EffectManager();
    static void LoadEffectManager(std::string address,float size);
    static int GetPlayEffect3D(std::string address);
    static int GetPlayEffect2D(std::string address);
    static bool IsPlayEffect(std::string address);
};