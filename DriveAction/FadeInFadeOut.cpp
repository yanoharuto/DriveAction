#include "FadeInFadeOut.h"
#include "DxLib.h"
#include "Utility.h"
FadeInFadeOut::FadeInFadeOut()
{
	fadeMode = FadeMode::fadeInStart;
}

FadeInFadeOut::~FadeInFadeOut()
{
}

void FadeInFadeOut::FadeIn(float deltaTime)
{

	switch (fadeMode)
	{
	case FadeMode::fadeInStart:

		if (colorValue < MAX1BYTEVALUE)
		{
			colorValue += fadeSpeed * deltaTime;
		}
		else
		{
			fadeMode = FadeMode::fadeInEnd;
		}
		break;
	case FadeMode::fadeInEnd:
		break;
	default:
		fadeMode = FadeMode::fadeInStart;
		break;
	}
}

void FadeInFadeOut::FadeOutStart()
{
	colorValue = MAX1BYTEVALUE;
	fadeMode = FadeMode::fadeOutStart;

}

void FadeInFadeOut::FadeInStart()
{
	colorValue = 0;
	fadeMode = FadeMode::fadeInStart;


}

void FadeInFadeOut::FadeOut(float deltaTime)
{
	switch (fadeMode)
	{
	case FadeMode::fadeOutStart:
		
		if (colorValue > 0)
		{
			colorValue -= fadeSpeed * deltaTime;
		}
		else
		{
			fadeMode = FadeMode::fadeOutEnd;
		}

		break;
	case FadeMode::fadeOutEnd:
		break;
	default:
		fadeMode = FadeMode::fadeOutStart;
		break;
	}
}

FadeMode FadeInFadeOut::GetFadeMode()
{
    return fadeMode;
}

void FadeInFadeOut::Draw()
{
	if (fadeMode != FadeMode::fadeInEnd)
	{
		DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GetColor(MAX1BYTEVALUE, MAX1BYTEVALUE, MAX1BYTEVALUE), true);
	}
}
