#include "NumUI.h"
#include "DxLib.h"
#include "Utility.h"
#include "OriginalMath.h"
NumUI::NumUI()
{
    LoadDivGraph(timerFontPass.c_str(), TIMER_FONT_NUM, TIMER_FONT_NUM, 1, fontSize, HUNDRED, numGraphHandle);
}

NumUI::~NumUI()
{
}

int NumUI::Draw(int x, int y, int num,float scale)
{
    //桁数
    int digits = pow(TIMER_FONT_NUM, OriginalMath::GetDigits(num) - 1);
    if (digits == 0)
    {
        DrawRotaGraph(x, y, scale, 0, numGraphHandle[0], true);
    }
    //桁数がゼロになるまで
    while (digits != 0)
    {
        //10のけたで割った時のあまり
        int drawNum = num / digits;
        DrawRotaGraph(x, y, scale, 0, numGraphHandle[drawNum], true);
        //フォントサイズ分横に
        x += scale * fontSize;
        num -= drawNum * digits;
        //桁数を下げる
        digits /= TIMER_FONT_NUM;
    }
    return x;
}

int NumUI::GetNumWidthSize()
{
    return fontSize;
}
