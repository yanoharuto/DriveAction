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
    //����
    int digits = pow(TIMER_FONT_NUM, OriginalMath::GetDigits(num) - 1);
    if (digits == 0)
    {
        DrawRotaGraph(x, y, scale, 0, numGraphHandle[0], true);
    }
    //�������[���ɂȂ�܂�
    while (digits != 0)
    {
        //10�̂����Ŋ��������̂��܂�
        int drawNum = num / digits;
        DrawRotaGraph(x, y, scale, 0, numGraphHandle[drawNum], true);
        //�t�H���g�T�C�Y������
        x += scale * fontSize;
        num -= drawNum * digits;
        //������������
        digits /= TIMER_FONT_NUM;
    }
    return x;
}

int NumUI::GetNumWidthSize()
{
    return fontSize;
}
