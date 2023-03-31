#include "PlayerRelatedUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "OriginalMath.h"
#include "UserInput.h"

PlayerRelatedUI::PlayerRelatedUI(Timer* setTimer, int setFirstCoinNum)
{
    timerUI = new TimerUI(drawTimerX, drawTimerY, fontSize, setTimer);
    minimapUI = new MiniMap();
    manualData.dataHandle = LoadGraph(manualPass.c_str());
    firstCoinNum = setFirstCoinNum;
    numUI = new NumUI();
    slashHandle = LoadGraph(slash.c_str());

}


PlayerRelatedUI::~PlayerRelatedUI()
{
    DeleteGraph(manualData.dataHandle);
    SAFE_DELETE(timerUI);
}

void PlayerRelatedUI::Update(PlayerRelatedInfo relatedInfo, std::list<VECTOR> setCoinPosList)
{
    minimapUI->Update(relatedInfo.objInfo,setCoinPosList);
    nowGetCoinNum = relatedInfo.hitCoinCount;
}

void PlayerRelatedUI::Draw()
{
    DrawGraph(manualData.x, manualData.y, manualData.dataHandle,true);
    
    int x = numUI->Draw(coinUIDrawX, coinUIDrawY, nowGetCoinNum, fontSize);
    x += numUI->GetNumWidthSize() * fontSize;
    DrawRotaGraph(x, coinUIDrawY, fontSize, 0, slashHandle, true);
    x += numUI->GetNumWidthSize() * fontSize;
    numUI->Draw(x , coinUIDrawY, firstCoinNum, fontSize);
    
    timerUI->Draw();
    if (UserInput::GetInputState(Space) == Hold)
    {
        minimapUI->Draw();
    }
}