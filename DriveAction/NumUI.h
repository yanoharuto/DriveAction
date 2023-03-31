#pragma once
#include <string>
#define TIMER_FONT_NUM 10
class NumUI
{
public:
    NumUI();
    ~NumUI();
    int Draw(int x, int y, int num,float scale);
    int GetNumWidthSize();
private:
    //�����̃t�H���g�摜�̃p�X
    const std::string timerFontPass = "data/NumFont.png";
    //�����̃t�H���g�摜
    int numGraphHandle[TIMER_FONT_NUM];
    //�����_�̉摜
    int pointGraphHandle;
    //�t�H���g�摜�̃T�C�Y
    const float fontSize = 80.0f;
};