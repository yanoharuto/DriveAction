#include "LapUI.h"
#include "Utility.h"
#include "DxLib.h"
LapUI::LapUI()
{
}

LapUI::LapUI(int maxLap)
{
    maxLapString = std::to_string(maxLap);
    UIData data = {};
    data.x = SCREEN_WIDTH / 15;
    data.y = SCREEN_HEIGHT / 24;
    data.dataHandle = CreateFontToHandle("BIZ UDƒSƒVƒbƒN", 64, 3, DX_FONTTYPE_NORMAL);
    lap = new StringUI(GetColor(255, 255, 255), data);
}

LapUI::~LapUI()
{
    SAFE_DELETE(lap);
}

void LapUI::Update(int nowLap)
{
    std::string string = "Lap::" + std::to_string(nowLap + 1) + "/" + maxLapString;
    lap->UpdateString(string);
}

void LapUI::Draw()
{
    lap->DrawUI();
}