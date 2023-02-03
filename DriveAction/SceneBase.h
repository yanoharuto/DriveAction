#pragma once
#include "FadeInFadeOut.h"
#include "Timer.h"
#include "Utility.h"
enum class SceneType
{
    TITLE,
    PLAY,
    RESULT
};

class SceneBase abstract
{
public:
    SceneBase(SceneType _SceneType)
    {
        nowScenType = _SceneType;
    }
    virtual ~SceneBase() 
    {
        SAFE_DELETE(timer);
        SAFE_DELETE(fadeInFadeOut);
    }
    virtual SceneType Update() = 0;
    virtual void Draw() = 0;
protected:
    SceneType nowScenType;
    FadeInFadeOut* fadeInFadeOut;
    Timer* timer;
};