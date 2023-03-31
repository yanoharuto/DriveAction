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
    //����
    int limit = timer->GetLimitTime() * HUNDRED;
    //�����B�������ʂ܂ŕ`�悷��
    int digits = HUNDRED * TIMER_FONT_NUM;
    //�`��ʒu
    float x = drawX;
    DrawRotaGraph(drawX + timerFontLoadSize * fontSize * 2, drawY, fontSize, 0, frameHandle, true);
    //�������[���ɂȂ�܂�
    while (digits != 0)
    {
        //10�̂����Ŋ��������̂��܂�
        int num = limit / digits;
        DrawRotaGraph(x, drawY, fontSize, 0, numGraphHandle[num], true);
        //�����_��`��
        if (digits == HUNDRED)
        {
            DrawRotaGraph(x, drawY, fontSize, 0, pointGraphHandle, true);
        }
        //�t�H���g�T�C�Y������
        x += timerFontLoadSize * fontSize;
        
        limit -= num * digits;
        //������������
        digits /= TIMER_FONT_NUM;
    }
}
