#include "StringUI.h"
#include "DxLib.h"

StringUI::StringUI()
{
    color = 0;
    uiData = {};
}

StringUI::StringUI(unsigned int colorValue,UIData data)
{
    color = colorValue;
    uiData = data;
}

StringUI::StringUI(unsigned int colorValue, UIData data, std::string str)
{
    color = colorValue;
    uiData = data;
    string = str;
}

StringUI::~StringUI()
{
    DeleteFontToHandle(uiData.dataHandle);
}

void StringUI::DrawRightAlignedString()
{
    DrawStringToHandle(uiData.x, uiData.y, string.c_str(), color, uiData.dataHandle);
}

void StringUI::DrawLeftAlignedString()
{
    DrawFormatStringToHandle(uiData.x, uiData.y, color, uiData.dataHandle,"%-s",string.c_str());
}

void StringUI::UpdateString(std::string updateString)
{
    string = updateString;
}