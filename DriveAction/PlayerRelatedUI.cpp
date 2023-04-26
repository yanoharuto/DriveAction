#include "PlayerRelatedUI.h"
#include "Utility.h"
#include "MiniMap.h"
#include "OriginalMath.h"
#include "UserInput.h"
#include "TimerUI.h"
#include "Timer.h"
#include "NumUI.h"
PlayerRelatedUI::PlayerRelatedUI(Timer* setTimer, int setFirstCoinNum)
{
    timerUI = new TimerUI(fontSize, setTimer);
    minimapUI = new MiniMap();
    manualData = UIManager::CreateUIData(manual);
    firstCoinNum = setFirstCoinNum;
    numUI = new NumUI();
    slashHandle = UIManager::CreateUIData(slash);
}


PlayerRelatedUI::~PlayerRelatedUI()
{
    SAFE_DELETE(timerUI);
    SAFE_DELETE(minimapUI);
}

void PlayerRelatedUI::Update(PlayerRelatedInfo relatedInfo, std::list<VECTOR> setCoinPosList)
{
    minimapUI->Update(relatedInfo.objInfo,setCoinPosList);
    nowGetCoinNum = relatedInfo.hitCoinCount;
}

void PlayerRelatedUI::Draw()
{
    DrawRotaGraph(manualData.x, manualData.y, manualData.size, 0, manualData.dataHandle[0], true);

    int x = numUI->Draw(coinUIDrawX, coinUIDrawY, nowGetCoinNum, fontSize);
    int result = DrawRotaGraph(x, coinUIDrawY, fontSize, 0, slashHandle.dataHandle[0], true);
    x += numUI->GetNumWidthSize() * fontSize;
    numUI->Draw(x, coinUIDrawY, firstCoinNum, fontSize);

    timerUI->Draw();
    minimapUI->Draw();
}