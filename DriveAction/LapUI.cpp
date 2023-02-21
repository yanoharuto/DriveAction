#include "LapUI.h"
#include "Utility.h"
#include "DxLib.h"
LapUI::LapUI()
{
    lap = nullptr;
}

LapUI::LapUI(int maxLap)
{
    maxLapString = std::to_string(maxLap);
    UIData data = {};
    data.x = SCREEN_WIDTH / 20 * 14.5f;
    data.y = SCREEN_HEIGHT / 20 * 2.5f;
    data.dataHandle = CreateFontToHandle("BIZ UDƒSƒVƒbƒN", 64, 3, DX_FONTTYPE_NORMAL);
    lap = new StringUI(GetColor(40, 40, 40), data);
}

LapUI::~LapUI()
{
    SAFE_DELETE(lap);
}

void LapUI::Update(int nowLap)
{
    std::string string = "Lap::" + std::to_string(nowLap) + "/" + maxLapString;
    lap->UpdateString(string);
}

void LapUI::Draw()
{
    lap->DrawRightAlignedString();
}