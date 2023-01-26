#include "PlayerRelatedUI.h"
#include "Utility.h"
PlayerRelatedUI::PlayerRelatedUI()
{

}

PlayerRelatedUI::PlayerRelatedUI(const int maxLap)
{
    UIData uiData;
    uiData.x = SCREEN_WIDTH / 13;
    uiData.y = SCREEN_HEIGHT / 9;
    uiData.dataHandle = CreateFontToHandle("BIZ UDƒSƒVƒbƒN", 64, 3, DX_FONTTYPE_NORMAL);
    rankUI = new StringUI(GetColor(0, 255, 0), uiData);
    lapUI = new LapUI(maxLap);
    reverseDrivingCautionUI = new ReverseDrivingCautionUI();
    uiData.x = SCREEN_WIDTH / 13 * 11;
    uiData.y = SCREEN_HEIGHT / 9;
    timeUI = new StringUI(GetColor(40,40,40), uiData);
}

PlayerRelatedUI::~PlayerRelatedUI()
{
    SAFE_DELETE(rankUI);
    SAFE_DELETE(lapUI);
    SAFE_DELETE(reverseDrivingCautionUI);
    SAFE_DELETE(timeUI);
}

void PlayerRelatedUI::Update(PlayerRelatedInfo relatedInfo,float deltaTime)
{
    reverseDrivingCautionUI->Update(relatedInfo.carDirection,relatedInfo.nextCheckPointDirection,deltaTime);
    rankUI->UpdateString(std::to_string(relatedInfo.rank));
    lapUI->Update(relatedInfo.lap);
    timeUI->UpdateString(std::to_string(relatedInfo.time));
}

void PlayerRelatedUI::Draw()
{
    reverseDrivingCautionUI->Draw();
    rankUI->DrawUI();
    lapUI ->Draw();
    timeUI->DrawUI();
}