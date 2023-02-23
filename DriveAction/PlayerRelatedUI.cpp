#include "PlayerRelatedUI.h"
#include "Utility.h"

PlayerRelatedUI::PlayerRelatedUI()
{

}

PlayerRelatedUI::PlayerRelatedUI(const int maxLap)
{
    UIData uiData;
    uiData.x = SCREEN_WIDTH / 20 * 14.5f;
    uiData.y = SCREEN_HEIGHT / 20 * 0.5f;
    uiData.dataHandle = CreateFontToHandle("BIZ UDゴシック", 102, 3, DX_FONTTYPE_NORMAL);
    rankUI = new StringUI(GetColor(0, 255, 0), uiData);
    lapUI = new LapUI(maxLap);
    uiData.dataHandle = CreateFontToHandle("BIZ UDゴシック", 64, 3, DX_FONTTYPE_NORMAL);
    reverseDrivingCautionUI = new ReverseDrivingCautionUI();
    uiData.x = SCREEN_WIDTH / 20 * 14.5f;
    uiData.y = SCREEN_HEIGHT / 20 * 4.0f;
    timeUI = new StringUI(GetColor(40,40,40), uiData);
    accelMeter = new AccelMeter();
    uiData.x = SCREEN_WIDTH / 20 * 2.8f;
    uiData.y = SCREEN_HEIGHT / 20 * 3;
    itemUI = new ItemUI(uiData);
    uiData.x = SCREEN_WIDTH / 20 * 2;
    uiData.y = SCREEN_HEIGHT / 20 * 15;
    uiData.dataHandle = LoadGraph("data/Description.png");
    descriptionUI = new ImgUI(1.0f,uiData);
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
    reverseDrivingCautionUI->Update(relatedInfo.reverse,deltaTime);
    rankUI->UpdateString("Rank::" + std::to_string(relatedInfo.rank));
    lapUI->Update(relatedInfo.lap + 1);
    
    std::string str = std::to_string(relatedInfo.time);
    str.erase(str.size() - eraseLength, eraseLength);
    timeUI->UpdateString("Time::" + str);
    accelMeter->Update(relatedInfo.accelPower,relatedInfo.accelPowerParcent);
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
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);//α値をいじる
    descriptionUI->DrawUI();
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//元に戻す
}