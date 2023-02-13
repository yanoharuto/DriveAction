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
    accelMeter = new AccelMeter();
    uiData.x = SCREEN_WIDTH / 2;
    uiData.y = SCREEN_HEIGHT / 13 * 2;
    itemUI = new ItemUI(uiData);
}

PlayerRelatedUI::~PlayerRelatedUI()
{
    SAFE_DELETE(rankUI);
    SAFE_DELETE(lapUI);
    SAFE_DELETE(reverseDrivingCautionUI);
    SAFE_DELETE(timeUI);
    SAFE_DELETE(accelMeter);
    SAFE_DELETE(itemUI);
}

void PlayerRelatedUI::Update(PlayerRelatedInfo relatedInfo,float deltaTime)
{
    reverseDrivingCautionUI->Update(relatedInfo.carDirection,relatedInfo.nextCheckPointDirection,deltaTime);
    rankUI->UpdateString(std::to_string(relatedInfo.rank));
    lapUI->Update(relatedInfo.lap + 1);
    timeUI->UpdateString(std::to_string(relatedInfo.time));
    accelMeter->Update(relatedInfo.accelPower);
    itemUI->Update(relatedInfo.itemTag);
}

void PlayerRelatedUI::Draw()
{
    reverseDrivingCautionUI->Draw();
    rankUI->DrawRightAlignedString();
    lapUI ->Draw();
    timeUI->DrawLeftAlignedString();
    accelMeter->Draw();
    itemUI->DrawUI();
}