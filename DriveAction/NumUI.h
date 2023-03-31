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
    //数字のフォント画像のパス
    const std::string timerFontPass = "data/NumFont.png";
    //数字のフォント画像
    int numGraphHandle[TIMER_FONT_NUM];
    //小数点の画像
    int pointGraphHandle;
    //フォント画像のサイズ
    const float fontSize = 80.0f;
};