#pragma once
#include "FadeMode.h"
class FadeInFadeOut
{
public:
    FadeInFadeOut();
    ~FadeInFadeOut();
    void FadeIn(float deltaTime);
    void FadeOutStart();
    void FadeInStart();
    void FadeOut(float deltaTime);
    FadeMode GetFadeMode();
    void Draw();
private:
    float colorValue = 0;
    const float fadeSpeed = 500.0f;
    FadeMode fadeMode;
};

