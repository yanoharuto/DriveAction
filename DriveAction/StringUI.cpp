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

StringUI::~StringUI()
{
    DeleteFontToHandle(uiData.dataHandle);
}

void StringUI::DrawUI()
{
    DrawStringToHandle(uiData.x,uiData.y,string.c_str(),color,uiData.dataHandle);
}

void StringUI::Update(std::string updateString)
{
    string = updateString;
}