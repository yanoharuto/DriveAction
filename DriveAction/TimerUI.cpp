#include "DxLib.h"
#include "TimerUI.h"
#include "Utility.h"
#include "Timer.h"
#include "UIManager.h"
#include "NumUI.h"
TimerUI::TimerUI()
{

}

TimerUI::TimerUI(float setFontSize, Timer* setTimer)
{
    fontSize = setFontSize;
    timer = setTimer;
    frameData = UIManager::CreateUIData(timerFrame);
    pointData = UIManager::CreateUIData(point);
    numUI = new NumUI();
    timerFontLoadSize = numUI->GetNumWidthSize();
}

TimerUI::~TimerUI()
{
    DeleteGraph(pointGraphHandle);
}

void TimerUI::Draw()
{
    //ŽžŠÔ
    float limit = timer->GetLimitTime();

    DrawRotaGraph(frameData.x + timerFontLoadSize * fontSize * 2, frameData.y, frameData.size, 0, frameData.dataHandle[0], true);
    numUI->Draw(frameData.x + numUI->GetNumWidthSize() * 2, frameData.y, limit, fontSize);
}
