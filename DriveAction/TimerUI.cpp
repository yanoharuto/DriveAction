#include "DxLib.h"
#include "TimerUI.h"
#include "Utility.h"
TimerUI::TimerUI()
{
    LoadDivGraph(timerFontPass.c_str(), TIMER_FONT_NUM, TIMER_FONT_NUM, 1, timerFontLoadSize, HUNDRED, numGraphHandle);
    pointGraphHandle = LoadGraph(pointFontPass.c_str());
}

TimerUI::TimerUI(float setX, float setY, float setFontSize, Timer* setTimer)
{
    drawX = setX;
    drawY = setY;
    fontSize = setFontSize;
    timer = setTimer;
    LoadDivGraph(timerFontPass.c_str(), TIMER_FONT_NUM, TIMER_FONT_NUM, 1, timerFontLoadSize, HUNDRED, numGraphHandle);
    pointGraphHandle = LoadGraph(pointFontPass.c_str());
    frameHandle = LoadGraph(framePass.c_str());
}

TimerUI::~TimerUI()
{
    DeleteGraph(pointGraphHandle);
    for (int i = 0; i < TIMER_FONT_NUM; i++)
    {
        DeleteGraph(numGraphHandle[i]);
    }
}

void TimerUI::Draw()
{
    //時間
    int limit = timer->GetLimitTime() * HUNDRED;
    //桁数。小数第二位まで描画する
    int digits = HUNDRED * TIMER_FONT_NUM;
    //描画位置
    float x = drawX;
    DrawRotaGraph(drawX + timerFontLoadSize * fontSize * 2, drawY, fontSize, 0, frameHandle, true);
    //桁数がゼロになるまで
    while (digits != 0)
    {
        //10のけたで割った時のあまり
        int num = limit / digits;
        DrawRotaGraph(x, drawY, fontSize, 0, numGraphHandle[num], true);
        //小数点を描画
        if (digits == HUNDRED)
        {
            DrawRotaGraph(x, drawY, fontSize, 0, pointGraphHandle, true);
        }
        //フォントサイズ分横に
        x += timerFontLoadSize * fontSize;
        
        limit -= num * digits;
        //桁数を下げる
        digits /= TIMER_FONT_NUM;
    }
}
