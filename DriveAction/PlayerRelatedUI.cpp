#include "PlayerRelatedUI.h"
#include "Utility.h"

PlayerRelatedUI::PlayerRelatedUI()
{
    UIData uiData;
    uiData.dataHandle = CreateFontToHandle("BIZ UDƒSƒVƒbƒN", 102, 3, DX_FONTTYPE_NORMAL);
    uiData.x = UI_SCREEN_WIDTH * 14.0f;
    uiData.y = UI_SCREEN_HEIGHT * 4.0f;
    timeUI = new StringUI(GetColor(200, 200, 40), uiData);
}


PlayerRelatedUI::~PlayerRelatedUI()
{
    SAFE_DELETE(timeUI);
}

void PlayerRelatedUI::Update(PlayerRelatedInfo relatedInfo,float deltaTime)
{
    std::string str = std::to_string(relatedInfo.scoreTime);
    str.erase(str.size() - eraseLength, eraseLength);
    timeUI->UpdateString("Time::" + str);
}

void PlayerRelatedUI::Draw()
{
    timeUI->DrawLeftAlignedString();
}