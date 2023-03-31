#pragma once
#include "FadeMode.h"
class FadeInFadeOut
{
public:
    FadeInFadeOut();
    ~FadeInFadeOut();
    void FadeIn();
    void FadeOutStart();
    void FadeInStart();
    void FadeOut();
    FadeMode GetFadeMode();
    void Draw();
private:
    float fadeValue = 0;
    const float fadeSpeed = 52.0f;
    FadeMode fadeMode;
};

