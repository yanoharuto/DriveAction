#include "StringUI.h"
#include "DxLib.h"

StringUI::StringUI()
{
    color = 0;
    stringData = {};
}

StringUI::StringUI(unsigned int colorValue,UIData data)
{
    color = colorValue;
    stringData = data;
}

StringUI::~StringUI()
{
    DeleteFontToHandle(stringData.dataHandle);
}

void StringUI::DrawUI()
{
    DrawStringToHandle(stringData.x,stringData.y,string.c_str(),color,stringData.dataHandle);
}

void StringUI::Update(std::string updateString)
{
    string = updateString;
}