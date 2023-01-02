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
    stringData = {};
}

StringUI::~StringUI()
{
    DeleteFontToHandle(stringData.dataHandle);
}

void StringUI::Draw()
{
}